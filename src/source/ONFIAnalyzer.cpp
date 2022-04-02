#include "ONFIAnalyzer.h"
#include "ONFIAnalyzerSettings.h"
#include <AnalyzerChannelData.h>



ONFIAnalyzer::ONFIAnalyzer()
:	Analyzer2(),
	mSettings( new ONFIAnalyzerSettings() )
{
	SetAnalyzerSettings( mSettings.get() );
}

ONFIAnalyzer::~ONFIAnalyzer()
{
	KillThread();
}

void ONFIAnalyzer::SetupResults()
{
	mResults.reset( new ONFIAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	if( mSettings->mCEChannel != UNDEFINED_CHANNEL )
		mResults->AddChannelBubblesWillAppearOn( mSettings->mCEChannel);
}

U8 ONFIAnalyzer::SyncAndReadDQ(U64 sample_number)
{
						  U8 data = 0;
							if(dqsChannel!=NULL)
							{
								dqsChannel->AdvanceToAbsPosition(sample_number);
								U8 b = (dqsChannel->GetBitState() == BIT_HIGH) ? 1 : 0;
								data |= b << 0;
							}
						  return data;
}

void ONFIAnalyzer::WorkerThread()
{
			analyzerNVDDRxx();
}


void ONFIAnalyzer::analyzerNVDDRxx()
{
				// get all data from channel
				ceChannel = GetAnalyzerChannelData( mSettings->mCEChannel);
				aleChannel = GetAnalyzerChannelData( mSettings->mALEChannel);
				cleChannel = GetAnalyzerChannelData( mSettings->mCLEChannel);
				weChannel = GetAnalyzerChannelData( mSettings->mWEChannel);
				reChannel = GetAnalyzerChannelData( mSettings->mREChannel);
				rbChannel= GetAnalyzerChannelData( mSettings->mRBChannel);
				dqsChannel= GetAnalyzerChannelData( mSettings->mDQSChannel);
				// list de channels datas
				dqChannel = GetAnalyzerChannelData( mSettings->mDQChannel);

				auto& ce_n = ceChannel;
				auto& ale =  aleChannel;
				auto& cle = cleChannel;
				auto& we_n = weChannel;
				auto& re = reChannel;
				auto& rb = rbChannel;
				auto& dqs = dqsChannel;
				auto& dq = dqChannel;


				while(true)
				{
							ReportProgress(ce_n->GetSampleNumber());
							if (ce_n->GetBitState() == BIT_HIGH)
										ce_n->AdvanceToNextEdge();

							const auto ce_n_f = ce_n->GetSampleNumber();
							we_n->AdvanceToAbsPosition(ce_n_f);
							ce_n->AdvanceToNextEdge();
							const auto ce_n_r = ce_n->GetSampleNumber();

							bool has_cmd = false;

							while(true)
							{
													const auto we_n_next = we_n->GetSampleOfNextEdge();
													const auto dqs_next = dqs->GetSampleOfNextEdge();

													const auto first_edge =
														has_cmd ? std::min(we_n_next, dqs_next) : we_n_next;

													if (first_edge >= ce_n_r)
																	break;

													// Be careful to give precedence to cmd/addr cycles
													we_n->AdvanceToAbsPosition(first_edge);
													dqs->AdvanceToAbsPosition(first_edge);
													const bool data_cycle =
													(first_edge != we_n_next) && (we_n->GetBitState() == BIT_HIGH);

													if (data_cycle)
													{
																				// TODO in some cases, DQ should be centered, not edge
																				U8 data = SyncAndReadDQ(first_edge);

																				// this is extremely fragile for some reason...Logic likes getting mad
																				U64 end = ce_n_r - 1;
																				if (dqs->DoMoreTransitionsExistInCurrentData())
																				{
																					end = std::min(end, dqs->GetSampleOfNextEdge());
																				}
																				AddFrame(kData, first_edge, end, data);

																				auto marker = (dqs->GetBitState() == BIT_HIGH)
																													? AnalyzerResults::MarkerType::UpArrow
																													: AnalyzerResults::MarkerType::DownArrow;
																				mResults->AddMarker(first_edge, marker, mSettings->mDQSChannel);
														}

													else if (we_n->GetBitState() == BIT_HIGH)
													{
															// WE_n rising
															const auto we_n_r = we_n->GetSampleNumber();
															mResults->AddMarker(we_n_r, AnalyzerResults::MarkerType::UpArrow,mSettings->mWEChannel);

															cle->AdvanceToAbsPosition(we_n_r);
															ale->AdvanceToAbsPosition(we_n_r);

															FrameType frame_type = kInvalid;
															U64 end{};
															if (cle->GetBitState() == BIT_HIGH)
															{
																has_cmd = true;
																frame_type = kCommand;
																end = cle->GetSampleOfNextEdge() - 1;
															}

															else if (ale->GetBitState() == BIT_HIGH)
															{
																	frame_type = kAddress;
																		end = std::min(we_n->GetSampleOfNextEdge(),
																		ale->GetSampleOfNextEdge()) -1;
															}
															else
															{
																	mResults->AddMarker(first_edge, AnalyzerResults::MarkerType::ErrorDot,mSettings->mCEChannel);
															}
															if (frame_type != kInvalid)
															{
																	U8 data = SyncAndReadDQ(we_n_r);
																	AddFrame(frame_type, we_n_r, end, data);
															}
											}


										}

								// send data to resultats to show up on saleae software
								AddFrame(kEnvelope, ce_n_f, ce_n_r);
								mResults->AddMarker(ce_n_r, AnalyzerResults::MarkerType::Stop, mSettings->mCEChannel);
								mResults->CommitPacketAndStartNewPacket();
								mResults->CommitResults();
					}
}

bool ONFIAnalyzer::AddFrame(FrameType frame_type,
                            U64 start,
                            U64 end,
                            U64 data1,
                            U64 data2,
                            U8 flags)
{
			  // NOTE: end - start must be > 0 or Logic crashes when trying to zoom to the
			  // frame
			  if (start >= end) {
			    return false;
			  }
			  Frame frame{};
			  frame.mStartingSampleInclusive = start;
			  frame.mEndingSampleInclusive = end;
			  frame.mType = frame_type;
			  frame.mData1 = data1;
			  frame.mData2 = data2;
			  frame.mFlags = flags;
			  mResults->AddFrame(frame);
			  ReportProgress(frame.mEndingSampleInclusive);
			  return true;
}

bool ONFIAnalyzer::NeedsRerun()
{	return false;}


U32 ONFIAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{	return 0;}

U32 ONFIAnalyzer::GetMinimumSampleRateHz()
{	return 0;}

const char* ONFIAnalyzer::GetAnalyzerName() const
{	return "ONFI Protocol";}

const char* GetAnalyzerName()
{	return "ONFI Protocol";}

Analyzer* CreateAnalyzer()
{	return new ONFIAnalyzer();}

void DestroyAnalyzer( Analyzer* analyzer )
{	delete analyzer;}
