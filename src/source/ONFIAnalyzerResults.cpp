#include "ONFIAnalyzerResults.h"
#include <AnalyzerHelpers.h>
#include "ONFIAnalyzer.h"
#include "ONFIAnalyzerSettings.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>


/**
* @brief Consctructor
*  @details ...
*
***************************************/
ONFIAnalyzerResults::ONFIAnalyzerResults( ONFIAnalyzer* analyzer, ONFIAnalyzerSettings* settings )
:	AnalyzerResults(),
	mSettings( settings ),
	mAnalyzer( analyzer )
{
}
/**
* @brief Destructor
*  @details ...
*
***************************************/
ONFIAnalyzerResults::~ONFIAnalyzerResults()
{
}

/**
* @brief function GenerateBubbleText
* @details
***************************/


struct HexCharStruct
{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
  return HexCharStruct(_c);
}

void ONFIAnalyzerResults::GenerateBubbleText( U64 frame_index,
	Channel& channel, DisplayBase display_base )
{
		ClearResultStrings();
		Frame frame = GetFrame( frame_index );
		std::string text;


	  const auto ft = (ONFIAnalyzer::FrameType)frame.mType;
	  const auto data = (U8)frame.mData1;

		std::string s;
		std::stringstream ss;
	  switch (ft)
		{
			  case ONFIAnalyzer::FrameType::kEnvelope:
			    // this is a fake type
			    return;
			  case ONFIAnalyzer::FrameType::kCommand:
				    //text = 'c';//fmt::format("CMD:{:02x}", data);

						ss << hex(data);
						ss >> s;
						text = "CMD: "+s;
				    break;
			  case ONFIAnalyzer::FrameType::kAddress:
					    //text = 'a' ;//fmt::format("ADDR:{:02x}", data);
							//std::string s;
							//std::stringstream ss;
							ss << hex(data);
							ss >> s;
							text = "ADDR: "+s;
					    break;
			  case ONFIAnalyzer::FrameType::kData:
					    //text = 'd';//fmt::format("DATA:{:02x}", data);
							//std::string s;
							//std::stringstream ss;
							ss << hex(data);
							ss >> s;
							text = "DATA: "+s;
					    break;
	  }

			AddResultString(text.c_str());

}



void ONFIAnalyzerResults::GenerateExportFile( const char* file, DisplayBase display_base, U32 export_type_user_id )
{
					std::ofstream file_stream(file, std::ios::out);
					struct Cycle
					{
					  ONFIAnalyzer::FrameType frame_type{ONFIAnalyzer::FrameType::kInvalid} ;
					  std::vector<U8> data;
					};

				using Packet = std::vector<Cycle>;
				Packet merged_packet;

				auto write_packet = [&file_stream](const Packet& packet)
				{
						 if (!packet.size()) { return; }
						 std::string line;
						 bool first = true;
						 for (const auto& e : packet)
						 {
										 if (first)
										 {
											 first = false;
										 }
										 else
										 {
											 line += " ";
										 }

										 switch (e.frame_type)
										 {
													 case ONFIAnalyzer::FrameType::kCommand:
														 line += "CMD:";
														 break;
													 case ONFIAnalyzer::FrameType::kAddress:
														 line += "ADDR:";
														 break;
													 case ONFIAnalyzer::FrameType::kData:
														 line += "DATA:";
														 break;
										 }
										 for (const auto& addr : e.data)
										 {
												 //line += fmt::format("{:02x}", addr);
													std::string s;
								 					std::stringstream ss;
								 					ss << hex(addr);
								 					ss >> s;
													line+= s;
										 }
				 			}
				 			file_stream << line << std::endl;
				};

				auto append_cycle = [](Packet* packet, ONFIAnalyzer::FrameType frame_type,U8 data)
				{
										 if (packet->size() && packet->back().frame_type == frame_type)
										 {
											 packet->back().data.push_back(data);
										 }
										 else
										 {
												 Cycle cycle ;
												 cycle.frame_type=frame_type;
												 std::vector<U8> vect;
												 vect.push_back(data);
												 cycle.data=vect;
												 packet->emplace_back(cycle);//Cycle{.frame_type = frame_type, .data = {data}});
										 }
				};

				const U64 num_frames = GetNumFrames();
				for (U64 frame_index = 0; frame_index < num_frames; frame_index++)
				{
							 Frame f = GetFrame(frame_index);
							 const auto ft = (ONFIAnalyzer::FrameType)f.mType;
							 const auto data = (U8)f.mData1;

							 switch (ft)
							 {
									 case ONFIAnalyzer::FrameType::kEnvelope:
										 write_packet(merged_packet);
										 merged_packet = {};
										 break;
									 case ONFIAnalyzer::FrameType::kCommand:
										 append_cycle(&merged_packet, ONFIAnalyzer::FrameType::kCommand, data);
										 break;
									 case ONFIAnalyzer::FrameType::kAddress:
										 append_cycle(&merged_packet, ONFIAnalyzer::FrameType::kAddress, data);
										 break;
									 case ONFIAnalyzer::FrameType::kData:
										 append_cycle(&merged_packet, ONFIAnalyzer::FrameType::kData, data);
										 break;
							 }

							 if (UpdateExportProgressAndCheckForCancel(frame_index, num_frames))
							 {
								 return;
							 }
				}

				write_packet(merged_packet);
				UpdateExportProgressAndCheckForCancel(num_frames, num_frames);
}

void ONFIAnalyzerResults::GenerateFrameTabularText( U64 frame_index, DisplayBase display_base )
{
		#ifdef SUPPORTS_PROTOCOL_SEARCH
			Frame frame = GetFrame( frame_index );
			ClearTabularText();

			char number_str[128];
			AnalyzerHelpers::GetNumberString( frame.mData1, display_base, 8, number_str, 128 );
			AddTabularText( number_str );
		#endif
}

void ONFIAnalyzerResults::GeneratePacketTabularText( U64 packet_id, DisplayBase display_base )
{
	//not supported

}

void ONFIAnalyzerResults::GenerateTransactionTabularText( U64 transaction_id, DisplayBase display_base )
{
	//not supported
}
