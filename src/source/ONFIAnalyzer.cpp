#include "ONFIAnalyzer.h"
#include "ONFIAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

/**/


ONFIAnalyzer::ONFIAnalyzer()
:	Analyzer2(),
<<<<<<< HEAD
mSettings( new ONFIAnalyzerSettings() ),
mSimulationInitilized( false )
=======
	mSettings( new ONFIAnalyzerSettings() )
>>>>>>> version_1
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
<<<<<<< HEAD
	mResults->AddChannelBubblesWillAppearOn( mSettings->mCEChannel );

=======
		mResults->AddChannelBubblesWillAppearOn( mSettings->mCEChannel);
>>>>>>> version_1
}

U8 ONFIAnalyzer::readData(U64 sample_number)
{
<<<<<<< HEAD
	U8 data = 0;
=======
						U8 data = 0;

						for(int i=0 ;i < dqChannel.size() ;i++ )
						{
							if(dqChannel[i]!=NULL)
								{
									dqChannel[i]->AdvanceToAbsPosition(sample_number);
									U8 b = (dqChannel[i]->GetBitState() == BIT_HIGH) ? 1 : 0;
									data |= b << i;
							 }
						}
						  return data;
}

void ONFIAnalyzer::WorkerThread()
{
			analyzerNVDDRxx();
}


void ONFIAnalyzer::analyzerNVDDRxx()
{

	ceChannel = GetAnalyzerChannelData( mSettings->mCEChannel);
	aleChannel = GetAnalyzerChannelData( mSettings->mALEChannel);
	cleChannel = GetAnalyzerChannelData( mSettings->mCLEChannel);
	weChannel = GetAnalyzerChannelData( mSettings->mWEChannel);
	reChannel = GetAnalyzerChannelData( mSettings->mREChannel);
	rbChannel= GetAnalyzerChannelData( mSettings->mRBChannel);
	dqsChannel= GetAnalyzerChannelData( mSettings->mDQSChannel);
	// list of all  channels datas to do
	dqChannel[0] = GetAnalyzerChannelData( mSettings->mDQChannel);
	dqChannel[1] = GetAnalyzerChannelData( mSettings->mDQ_1Channel);
	dqChannel[2] = GetAnalyzerChannelData( mSettings->mDQ_2Channel);
	dqChannel[3] = GetAnalyzerChannelData( mSettings->mDQ_3Channel);
	dqChannel[4] = GetAnalyzerChannelData( mSettings->mDQ_4Channel);
	dqChannel[5] = GetAnalyzerChannelData( mSettings->mDQ_5Channel);
	dqChannel[6] = GetAnalyzerChannelData( mSettings->mDQ_6Channel);
	dqChannel[7] = GetAnalyzerChannelData( mSettings->mDQ_7Channel);
	//dqChannels_2 = GetAnalyzerChannelData( mSettings->mDQ_2Channel);

	auto& ce_n = ceChannel;
	auto& ale =  aleChannel;
	auto& cle = cleChannel;
	auto& we_n = weChannel;
	auto& re = reChannel;
	auto& rb = rbChannel;
	auto& dqs = dqsChannel;
	//auto& dq = dqChannel;


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
																	U8 data = readData(first_edge);

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
														U8 data = readData(we_n_r);
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
>>>>>>> version_1

	/*	if(mALEChannel != NULL)
	{
	mALEChannel->AdvanceToAbsPosition(sample_number);
	U8 b = (mALEChannel->GetBitState() == BIT_HIGH) ? 1 : 0;
	data |= b << 0;
}
<<<<<<< HEAD
if(mCEChannel != NULL)
{
mCEChannel->AdvanceToAbsPosition(sample_number);
U8 b = (mCEChannel->GetBitState() == BIT_HIGH) ? 1 : 0;
data |= b << 1;
}
if(mCLEChannel != NULL)
{
mCLEChannel->AdvanceToAbsPosition(sample_number);
U8 b = (mCLEChannel->GetBitState() == BIT_HIGH) ? 1 : 0;
data |= b << 2;
}
if(mREChannel != NULL)
{
mREChannel->AdvanceToAbsPosition(sample_number);
U8 b = (mREChannel->GetBitState() == BIT_HIGH) ? 1 : 0;
data |= b << 4;
}
if(mWEChannel != NULL)
{
mWEChannel->AdvanceToAbsPosition(sample_number);
U8 b = (mWEChannel->GetBitState() == BIT_HIGH) ? 1 : 0;
data |= b << 5;
}*/
if(mDQSChannel!=NULL)
{
	mDQSChannel->AdvanceToAbsPosition(sample_number);
	U8 b = (mDQSChannel->GetBitState() == BIT_HIGH) ? 1 : 0;
	data |= b << 0;
}
return data;
}

/**
*  @brief WorkerThread
*  @ details the heart of our Analyzer ...
*******************/

//AnalyzerChannelData give the data from a particular input
void ONFIAnalyzer::WorkerThread()
{

	// get all data from channel
	mALEChannel = GetAnalyzerChannelData( mSettings->mALEChannel );
	mCEChannel = GetAnalyzerChannelData( mSettings->mCEChannel );
	mCLEChannel = GetAnalyzerChannelData( mSettings->mCLEChannel );
	mREChannel = GetAnalyzerChannelData( mSettings->mREChannel );
	mWEChannel = GetAnalyzerChannelData( mSettings->mWEChannel );
	mDQSChannel = GetAnalyzerChannelData( mSettings->mDQSChannel );


	// a cycle begins with CE_n falling edge
	// WE_n rising edge then clocks status of CLE and ALE
	// DQ is clocked by DQS *centered* (for DDR)
	auto& ce_n = mCEChannel;
	auto& cle = mCLEChannel;
	auto& ale =  mALEChannel;
	auto& we_n = mWEChannel;
	auto& re = mREChannel;
	auto& dqs = mDQSChannel;

	// the analyzant of data
	while(true)
	{
		ReportProgress(ce_n->GetSampleNumber());

		// Sync CE_n and WE_n when CE_n is low/falling
		if (ce_n->GetBitState() == BIT_HIGH)
		ce_n->AdvanceToNextEdge();

		const auto ce_n_f = ce_n->GetSampleNumber();
		we_n->AdvanceToAbsPosition(ce_n_f);
		// Advance CE_n to rising
		ce_n->AdvanceToNextEdge();
		const auto ce_n_r = ce_n->GetSampleNumber();

		bool has_cmd = false;

		while(true)
		{
			const auto we_n_next = we_n->GetSampleOfNextEdge();
			const auto dqs_next = dqs->GetSampleOfNextEdge();

			const auto first_edge = has_cmd ? std::min(we_n_next, dqs_next) : we_n_next;

			if (first_edge >= ce_n_r)
			break;

			// Be careful to give precedence to cmd/addr cycles
			we_n->AdvanceToAbsPosition(first_edge);
			dqs->AdvanceToAbsPosition(first_edge);
			const bool data_cycle = (first_edge != we_n_next) && (we_n->GetBitState() == BIT_HIGH);

			if (data_cycle)
			{
				/*	// TODO in some cases, DQ should be centered, not edge
				U8 data = SyncAndReadDQ(first_edge);

				// this is extremely fragile for some reason...Logic likes getting mad
				U64 end = ce_n_r - 1;
				if (dqs->DoMoreTransitionsExistInCurrentData()) {
				end = std::min(end, dqs->GetSampleOfNextEdge());
			}
			AddFrame(kData, first_edge, end, data);

			auto marker = (dqs->GetBitState() == BIT_HIGH)
			? AnalyzerResults::MarkerType::UpArrow
			: AnalyzerResults::MarkerType::DownArrow;
			mResults->AddMarker(first_edge, marker, mSettings->mDQSChannel);*/
		}

		else if (we_n->GetBitState() == BIT_HIGH)
		{
			// WE_n rising
			const auto we_n_r = we_n->GetSampleNumber();
			mResults->AddMarker(we_n_r, AnalyzerResults::MarkerType::UpArrow, mSettings->mWEChannel);

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
				ale->GetSampleOfNextEdge()) -	1;
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

	AddFrame(kEnvelope, ce_n_f, ce_n_r);
	mResults->AddMarker(ce_n_r, AnalyzerResults::MarkerType::Stop, mSettings->mCEChannel);
	// why doesn't this generate a packet :(
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
	/**
	*  @brief NeedsRerun
	*	@details this function is called when the analyzer has finished
	*  @return true for run over again the same data or false to not
	**/
	bool ONFIAnalyzer::NeedsRerun()
	{
		return false;
	}

	/**
	*  @brief GenerateSimulationData
	*  @details function called to get simulated data
	****/
	U32 ONFIAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
	{
		return 0;
	}


	/**
	*  @brief GetMinimumSampleRateHz
	*  @details This function check if the  selected sample rate is sufficient
	*		to get good results for the analyzer.
	**************/
	U32 ONFIAnalyzer::GetMinimumSampleRateHz()
	{
		return 0;
	}

	/**
	* @brief GetAnalyzerName
	* @details return the Analyzer' name
	**************/
	const char* ONFIAnalyzer::GetAnalyzerName() const
	{
		return "ONFI Protocol";
	}

	/**
	* @brief GetAnalyzerName
	* @details return the Analyzer' name
	**************/

	const char* GetAnalyzerName()
	{
		return "ONFI Protocol";
	}

	/**
	* @brief CreateAnalyzer
	* @details
	**************/
	Analyzer* CreateAnalyzer()
	{
		return new ONFIAnalyzer();
	}

	/**
	* @brief DestroyAnalyzer
	* @details this function Simply call delete on the provided pointer.
	**************/

	void DestroyAnalyzer( Analyzer* analyzer )
	{
		delete analyzer;
	}
=======

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
{
		//not implemented
	return 0;
}

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


/* may be
// get all data from channel
				ceChannel = GetAnalyzerChannelData( mSettings->mCEChannel);
				aleChannel = GetAnalyzerChannelData( mSettings->mALEChannel);
				cleChannel = GetAnalyzerChannelData( mSettings->mCLEChannel);
				weChannel = GetAnalyzerChannelData( mSettings->mWEChannel);
				reChannel = GetAnalyzerChannelData( mSettings->mREChannel);
				rbChannel= GetAnalyzerChannelData( mSettings->mRBChannel);
				dqsChannel= GetAnalyzerChannelData( mSettings->mDQSChannel);
				// list of all  channels datas to do
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
																				U8 data = readData(first_edge);

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
																	U8 data = readData(we_n_r);
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
*/

/* good too 
// get all data from channel
ceChannel = GetAnalyzerChannelData( mSettings->mCEChannel);
aleChannel = GetAnalyzerChannelData( mSettings->mALEChannel);
cleChannel = GetAnalyzerChannelData( mSettings->mCLEChannel);
weChannel = GetAnalyzerChannelData( mSettings->mWEChannel);
reChannel = GetAnalyzerChannelData( mSettings->mREChannel);
rbChannel= GetAnalyzerChannelData( mSettings->mRBChannel);
dqsChannel= GetAnalyzerChannelData( mSettings->mDQSChannel);
// list of all  channels datas to do
dqChannel[0] = GetAnalyzerChannelData( mSettings->mDQChannel);
dqChannel[1] = GetAnalyzerChannelData( mSettings->mDQ_1Channel);
dqChannel[2] = GetAnalyzerChannelData( mSettings->mDQ_2Channel);
dqChannel[3] = GetAnalyzerChannelData( mSettings->mDQ_3Channel);
dqChannel[4] = GetAnalyzerChannelData( mSettings->mDQ_4Channel);
dqChannel[5] = GetAnalyzerChannelData( mSettings->mDQ_5Channel);
dqChannel[6] = GetAnalyzerChannelData( mSettings->mDQ_6Channel);
dqChannel[7] = GetAnalyzerChannelData( mSettings->mDQ_7Channel);

auto& ce_n = ceChannel;
auto& ale =  aleChannel;
auto& cle = cleChannel;
auto& we_n = weChannel;
auto& re = reChannel;
auto& rb = rbChannel;
auto& dqs = dqsChannel;
auto& dq = dqChannel[0];


while(true)
{
			ReportProgress(ce_n->GetSampleNumber());
			if (ce_n->GetBitState() == BIT_HIGH)
						ce_n->AdvanceToNextEdge();

											const auto ce_n_f = ce_n->GetSampleNumber();
											re->AdvanceToAbsPosition(ce_n_f);
											ce_n->AdvanceToNextEdge();
											const auto ce_n_r = ce_n->GetSampleNumber();

										 if(re->GetBitState()==BIT_HIGH)
										 {

																	 cle->AdvanceToAbsPosition(re->GetSampleNumber());
																	 ale->AdvanceToAbsPosition(re->GetSampleNumber());
																	 we_n->AdvanceToAbsPosition(re->GetSampleNumber());

																	 const auto we_n_r = we_n->GetSampleNumber();
																	 mResults->AddMarker(we_n_r, AnalyzerResults::MarkerType::UpArrow,mSettings->mWEChannel);

																	 FrameType frame_type = kInvalid;
																	 U64 end{};
																	 if (cle->GetBitState() == BIT_HIGH)
																	 {

																		 frame_type = kCommand;
																		 end = cle->GetSampleOfNextEdge() - 1;
																	 }

																	 else if (ale->GetBitState() == BIT_HIGH)
																	 {
																				 frame_type = kAddress;
																				 end = ale->GetSampleOfNextEdge() - 1;
																				 //end = std::min(we_n->GetSampleOfNextEdge(),ale->GetSampleOfNextEdge()) -1;
																	 }
																	 else if(we_n->GetBitState()==BIT_HIGH && cle->GetBitState()==BIT_LOW && ale->GetBitState()==BIT_LOW)
																	 {
																			 //mResults->AddMarker(first_edge, AnalyzerResults::MarkerType::ErrorDot,mSettings->mCEChannel);
																	 }
																	 if (frame_type != kInvalid)
																	 {
																			 U8 data = readData(we_n_r);
																			 AddFrame(frame_type, we_n_r, end, data);
																	 }
										 }
										 else
										 {
													const auto ce_n_f = ce_n->GetSampleNumber();
													re->AdvanceToAbsPosition(ce_n_f);
													ce_n->AdvanceToNextEdge();
													const auto ce_n_r = ce_n->GetSampleNumber();
													const auto we_n_r = we_n->GetSampleNumber();

													cle->AdvanceToAbsPosition(re->GetSampleNumber());
													ale->AdvanceToAbsPosition(re->GetSampleNumber());
													we_n->AdvanceToAbsPosition(re->GetSampleNumber());

													if(we_n->GetBitState()==BIT_HIGH && cle->GetBitState()==BIT_LOW && ale->GetBitState()==BIT_LOW)
													{

													}
										 }


		 // send data to resultats to show up on saleae software
			AddFrame(kEnvelope, ce_n_f, ce_n_r);
			mResults->AddMarker(ce_n_r, AnalyzerResults::MarkerType::Stop, mSettings->mCEChannel);
			mResults->CommitPacketAndStartNewPacket();
			mResults->CommitResults();
	}
*/
>>>>>>> version_1
