#include <iostream>

#include <strings.h>

#include "musicbrainz4/Query.h"
#include "musicbrainz4/GenericList.h"
#include "musicbrainz4/Release.h"
#include "musicbrainz4/ReleaseGroup.h"
#include "musicbrainz4/Medium.h"
#include "musicbrainz4/NameCredit.h"
#include "musicbrainz4/ArtistCredit.h"
#include "musicbrainz4/Artist.h"
#include "musicbrainz4/HTTPFetch.h"
#include "musicbrainz4/Track.h"
#include "musicbrainz4/Recording.h"

void LoadTest();
std::string AlbumType(const std::string Type);
std::string AlbumStatus(const std::string Status);
void WaitRequest();

int main(int argc, const char *argv[])
{
//	LoadTest();

//	return 0;

	MusicBrainz4::CQuery MB;

	//MusicBrainz4::CRelease Test=MB.LookupRelease("8fd13191-2d9a-4670-b789-0c99a06278e0");
	//MusicBrainz4::CRelease Test=MB.LookupRelease("ae8c2094-f3a8-45f8-8c1b-09d069425526");
	//std::cout << Test << std::endl;
	//return 0;

	std::string DiscID="arIS30RPWowvwNEqsqdDnZzDGhk-";
	//DiscID="kXyckpXOUugZwZXFrAo5jbsap88-";

	if (argc==2)
		DiscID=argv[1];

	MusicBrainz4::CGenericList<MusicBrainz4::CRelease> ReleaseList=MB.LookupDiscID(DiscID);

	std::vector<MusicBrainz4::CRelease>Releases=ReleaseList.Items();
	std::vector<MusicBrainz4::CRelease>::const_iterator ThisRelease=Releases.begin();
	while (ThisRelease!=Releases.end())
	{
		MusicBrainz4::CRelease Release=(*ThisRelease);

		MusicBrainz4::CRelease FullRelease=MB.LookupRelease(Release.ID());

		std::cout << "Full release: " << std::endl;

		std::cout << FullRelease << std::endl;

		std::cout << "Release group title: '" << FullRelease.ReleaseGroup()->Title() << "'" << std::endl;

		std::cout << std::endl << std::endl << "Media matching " << DiscID << ":" << std::endl;

		std::vector<MusicBrainz4::CMedium> Media=FullRelease.MediaMatchingDiscID(DiscID);
		std::vector<MusicBrainz4::CMedium>::const_iterator ThisMedium=Media.begin();
		while (ThisMedium!=Media.end())
		{
			std::cout << *ThisMedium << std::endl;

			++ThisMedium;
		}

		std::cout << std::endl << std::endl;

		++ThisRelease;
	}

	return 0;
}

void LoadTest()
{
	std::vector<std::string> DiscIDs;
	DiscIDs.push_back("arIS30RPWowvwNEqsqdDnZzDGhk-");
	DiscIDs.push_back("kXyckpXOUugZwZXFrAo5jbsap88-");
	DiscIDs.push_back("Jm179QQTLC5nMygsPonxvh.ol1E-");
	DiscIDs.push_back("yaEsEx7O.ZAM3aXooTSBGawJY8M-");
	DiscIDs.push_back("4u8PFdcWYt3D8d03hRFQnz2JY_o-");
	DiscIDs.push_back("AB12Fy4NMHcV7o5ADcvL.gBANHs-");
	DiscIDs.push_back("4tWWOLPDZN8xrglYQjp0CM0iRKY-");
	DiscIDs.push_back("rdLVlW26wU8QKRGjMlcl92F0jAE-");
	DiscIDs.push_back("8sbBUt2f9obhnBiVd_WR6w8yGJY-");
	DiscIDs.push_back("OqX_r.nOOvCSmBaL0_FfQ9tIUko-");
	DiscIDs.push_back("k04vEQ.Mu5uX0ronQGm.Ndn4rYg-");
	DiscIDs.push_back("shnBMUn0eaZ.snl7Pb9ujdzy56w-");
	DiscIDs.push_back("tBy6Bu5xqZ5k_gTRg30kF1353Bk-");
	DiscIDs.push_back("GRBwyFp5.wWdrzcY.WaCW.WbiEo-");
	DiscIDs.push_back("5P_k.hDRD4MeZXcb_u0qOxq5xZM-");
	DiscIDs.push_back(".m7fRJJlbilsCTh2jBsCd6GqTgk-");
	DiscIDs.push_back("hnN7egdEWn_0CTk4qMrZYjP4POI-");
	DiscIDs.push_back("WsXxoGJLa4D5PjcqoCj3J73phEk-");
	DiscIDs.push_back("N3gQVG8i737MnsXx4nhsbVNkpkI-");
	DiscIDs.push_back("GtuQoRWI_LxeFozWggr5amQvQ6o-");
	DiscIDs.push_back("cPh3jXVQ_tzmVzmochGjtBsm0KM-");
	DiscIDs.push_back("oWMQbuewoX2jIdKiVK0hZmHFTAQ-");
	DiscIDs.push_back("e05_reBx0FNFMTlIuRpwT7lCveA-");
	DiscIDs.push_back("YuRX7aRXY4_GZxx5PRCFNDqWxlI-");
	DiscIDs.push_back("MUguYrmw9cmrE05qUO7.3K1PjoQ-");
	DiscIDs.push_back("0tnR6rKA8KinRdfbYg1.j9.wMB0-");
	DiscIDs.push_back("eDeI7CTRPazKiHDJG4WJQClBQ0Q-");
	DiscIDs.push_back("xpyS9f2l_Hft_hj6XqcnGZODPf8-");
	DiscIDs.push_back("1cZpGb6sPCRhy5H0eJbtNKohKRs-");
	DiscIDs.push_back("Bx.Gz2896ygzAFjidIJ7BeesYds-");
	DiscIDs.push_back("sH4qZsequiDjAYcDdQF00YgYJG0-");
	DiscIDs.push_back("ZmOvFYm3RP8veIUxIiSxy8jpg0E-");
	DiscIDs.push_back("lo77mYaRG0S8mCpMT7FDreNHv60-");
	DiscIDs.push_back("CO.78OO1O8RXWUQlc53avIzAD8c-");
	DiscIDs.push_back("9Y9Qq_dZxo0jBqIod6GT6zZBW7g-");
	DiscIDs.push_back("Lbq7QRH.N8Kh30K0M6XfqaMKad0-");
	DiscIDs.push_back("MkqsUEWspcNt5K_ufLFkSQG7ZZ8-");
	DiscIDs.push_back("VGgkXW1yVeSvjGv8DgVzUNm3rvg-");
	DiscIDs.push_back("S7lekT9lBDz17A_O6PkjpIZ7h3Q-");
	DiscIDs.push_back("rK2tHTK4cyFlrC_Um9_6q.REur4-");
	DiscIDs.push_back("Zf2lZDdgyhHvrXolJGP5yj0z85k-");
	DiscIDs.push_back("GIw2k85qJmWgoFXcRBs6kurG5O0-");
	DiscIDs.push_back("PwrisOC5K5ya9_pNU8uhWfL1_40-");
	DiscIDs.push_back("XFiZYT0fxXw.3nVhZpNoT0kUVrE-");
	DiscIDs.push_back("ZrdeI.9ekevCnNqivflPvOBUPIo-");
	DiscIDs.push_back("Rj4m1X0oEK1f_ets5ypxp_afuU0-");
	DiscIDs.push_back("r_RTSmtd2QtHspG125elHOB2qH0-");
	DiscIDs.push_back("04lVzq9LUlhb8lDSmGnQ2pyUK78-");
	DiscIDs.push_back("qYf0sWfSNOhAFh9DA1F2.H2qdEU-");
	DiscIDs.push_back("4PC8Aoy_mXybtYLzYxZuH0q_ZmQ-");
	DiscIDs.push_back("L9ARv6.yk0QVD3CgqN0y2s9xuzw-");
	DiscIDs.push_back("yBfulJrq_gVEP4M3_qD1jcKMvKM-");
	DiscIDs.push_back("Wa4rxjX1m8dQR4O8GOIJhE1X2cM-");
	DiscIDs.push_back("y0bEiMmgh58nHTcgFSDaBjn9gLU-");
	DiscIDs.push_back("25Oz.v0mvDU_IbTeAHw7O4mUyIU-");
	DiscIDs.push_back("XRf2BRPyCb2OGOVV_r30QNGP8tQ-");
	DiscIDs.push_back("dEgqwL_qeGmyHCoUD0YgySt.1fo-");
	DiscIDs.push_back("8bpMF2UJJRT.k1Zy7D3YNGOMBqQ-");
	DiscIDs.push_back("Xj2DIIyok6uT2TUTezhFRMJerHg-");
	DiscIDs.push_back("kN.Ov.enzyJS8vV2xpOuoX_AeoU-");
	DiscIDs.push_back("AaoNZd5CpWlYvF6X2RmD1qT_5tw-");
	DiscIDs.push_back("Y0gUsQKzGPfTzsXZAicw.w9FmR4-");
	DiscIDs.push_back("OvWjg.r6b0CBjNSbY9H5aGocsHc-");
	DiscIDs.push_back("6of8YnGaHoXgQBaRLrCPHOvJcBs-");
	DiscIDs.push_back("tLGBAiCflG8ZI6lFcOt87vXjEcI-");
	DiscIDs.push_back("IeldkVfIh1wep_M8CMuDvA0nQ7Q-");
	DiscIDs.push_back("dFrA.sy2V.RGd4JXTvYaAYO3sxY-");
	DiscIDs.push_back("2Hk9C_hPo0Ju3kEg7K464Md7nt4-");
	DiscIDs.push_back("zR3kVS6hV5NgOHA1ZkZqPx6RELo-");
	DiscIDs.push_back("PtJQ0NlAVEa7AA.Icet3i623s34-");
	DiscIDs.push_back("4e0eVKblphGiCNxB_xlKK_6zOt0-");
	DiscIDs.push_back("YdxNIjpQXgjFPgbiKFWS_TUYZRA-");
	DiscIDs.push_back("CI31ktO9S6FT2ImoTrttokacOKg-");
	DiscIDs.push_back("BMM1eubmolf8EZcvbUgsHlK8BcU-");
	DiscIDs.push_back("Td9CGk2M2s7S6VSFSvecBjDKtmg-");
	DiscIDs.push_back("g8lGJnlHO6zbXWJYCOYS1_Qpowk-");
	DiscIDs.push_back("WtKVvRf0LgeYqI9eTWZzjQoCslk-");
	DiscIDs.push_back("CmVEtxNAKoqEPvJLVdi_hSuKNHw-");
	DiscIDs.push_back("OfSR2G.90qgwqVpCdjLrjW.Hy80-");
	DiscIDs.push_back("oJulDELorg75UuinzXRqNzVz2T8-");
	DiscIDs.push_back("XAPBOo7xBvj4KDJxuEZsPx5tmHI-");
	DiscIDs.push_back("nIDrTG_DHGA9S.6.kzjb9zGOZXI-");
	DiscIDs.push_back("WNylbIWG0Od4.FUSUtx6ryv_Fec-");
	DiscIDs.push_back("IE.hOQoFDPA.zbOke_TUXvbxCPw-");
	DiscIDs.push_back("mMdGYpX8Hl1Syts1YiZ62FcuNLA-");
	DiscIDs.push_back("xtIUSAkvXkbXbFSCQYMhzaC0DM4-");
	DiscIDs.push_back("5EirQgFMp9nihsMg.uUUhBb1je4-");
	DiscIDs.push_back("uHhzaPsArQ4lAp3FocqGCOt7Cao-");
	DiscIDs.push_back("3FYpA.BtuNdNnZuH1c6RtJE3Hl0-");
	DiscIDs.push_back("hOyEq3XQ90iNVzTomdV8qrbFeto-");
	DiscIDs.push_back("3.JSYnoqsoyPsbpIDzPWmPqGiRc-");
	DiscIDs.push_back("rRp5JEEQ.KRR2Q_MjlKd.1yf45Q-");
	DiscIDs.push_back("2vNmb7f_ajeb4HzlOhrzp_sl4w8-");
	DiscIDs.push_back("fQrbmmC4_AQua05LuKXH.InkkSI-");
	DiscIDs.push_back("b3QM2VkELOrVhett7kN7R5hhnvs-");
	DiscIDs.push_back("sf239bWIjL7GyCiEQGA2eE_goJQ-");
	DiscIDs.push_back("dcvV_v_BiNoVZBI4.s6svlQCglE-");
	DiscIDs.push_back("VJNo6GLZFkXbyon7bFa1jkEqNNk-");
	DiscIDs.push_back("kgQrlgUmdbRDMjsXttzS4uZ4D8c-");
	DiscIDs.push_back("E6owtg6TWGpCAy9HXq0H40mAGMA-");
	DiscIDs.push_back("y879QAMVZA.gsBa_4QOXy_SSzXs-");
	DiscIDs.push_back("97qdbkCglcLbi55G0ZW6K6u3G64-");
	DiscIDs.push_back("fiOAciPzXBMSgC_0Fm.AZ4V3tKg-");
	DiscIDs.push_back("opRZ3tLu7aE0HtEPi3sMvJqOBDI-");
	DiscIDs.push_back("TtCsoyi67uptOckJO7619MVqvDI-");
	DiscIDs.push_back("0lEFfUGuoI_8ZZaBXQ3tlMcQbHI-");
	DiscIDs.push_back("YZGb6g_jC2E6KzhiRnWAS9uhzXc-");
	DiscIDs.push_back("xA3p59dQpJpDXZYHz1SSQ491oaU-");
	DiscIDs.push_back("4YJoCTQ4GbRF6gegeEeFOrbL7NE-");
	DiscIDs.push_back("up.BVe0wVJpb4V1XYtpAhIPlh6E-");
	DiscIDs.push_back("QDL_K53IIgvHQ3ewF1KuCCd_ddo-");
	DiscIDs.push_back("Oqs0HoDJtdfE.qdho7v4JjREp8g-");
	DiscIDs.push_back("VT8JtbSWevIg0wmZ6Oga.5aFI3k-");
	DiscIDs.push_back("WB6dfxGddF2r_gruNtHOqK2UyfU-");
	DiscIDs.push_back("bzzipXpXibLHMoJRoyTwsEMkGJE-");
	DiscIDs.push_back("nMbQ4LATRI6.qDv5Y5QFbpZzTv8-");
	DiscIDs.push_back("amfFdPjXibAT0JgOgyqxiHhpthI-");
	DiscIDs.push_back("09ErAg0zG0NB4tRhgLbZJDcK9wI-");
	DiscIDs.push_back("kjKc5fyl4H1KLvf45yfJ9Rp4IJA-");
	DiscIDs.push_back(".9qHDkcdofXv2MGrFTHJn_xARS0-");
	DiscIDs.push_back("kRZkgWDVgClKPMIvKOMU0wIyvlU-");
	DiscIDs.push_back("KQBAiLM2xJPspju4zws_VWO53b4-");
	DiscIDs.push_back("EEn1BbkrAYZ9jhJlMFVeFPzflP8-");
	DiscIDs.push_back("WPhGrvRMC9Ifdp10bRLvOR.2CQA-");
	DiscIDs.push_back("yDWXOXDNZi90RSiijONnAmzvBQA-");
	DiscIDs.push_back("_IW8yQi.QH1yqOt7O7KdbaBii4Q-");
	DiscIDs.push_back("H05gUO_Q7__mpsCa9PkxhRqg44c-");
	DiscIDs.push_back("60yigclB0BsMUF5ynOr35oVfczM-");
	DiscIDs.push_back("KLEN7Ssdg1cuuFB9MXciY6x.bMI-");
	DiscIDs.push_back("KNyE7H7LcwmzRtcXuh.968QvUDM-");
	DiscIDs.push_back("_8zR_z32WdqmGk2gzr.Lmg_1pCA-");
	DiscIDs.push_back("FL3eCYRSeIz.Ti6wRFQulW5MxfY-");
	DiscIDs.push_back("nMicof9sUrvC1_Xn5XNU1SwufKU-");
	DiscIDs.push_back("3S_9q9HuOzmdkFK_FA5VR2uCBh0-");
	DiscIDs.push_back("JNx1eZVSlWiwhUi_Rc8SfltQ.Wo-");
	DiscIDs.push_back("iFFX7onCnW04.iut9vCmtdQS3VU-");
	DiscIDs.push_back("CL9ib6Vrs.zbwQtLOdv2h7ACnuE-");
	DiscIDs.push_back("zYWylyqObrI6baiyHVkTv25TmIY-");

	std::vector<std::string>::const_iterator ThisID=DiscIDs.begin();
	while (ThisID!=DiscIDs.end())
	{
		std::string DiskID=*ThisID;
		std::cout << std::endl << std::endl << "DiscID: " << DiskID << std::endl;

		MusicBrainz4::CQuery MusicBrainz;

		WaitRequest();

		MusicBrainz4::CGenericList<MusicBrainz4::CRelease> ReleaseList=MusicBrainz.LookupDiscID(DiskID);
		std::vector<MusicBrainz4::CRelease> Releases=ReleaseList.Items();

		if (Releases.size())
		{
			std::vector<MusicBrainz4::CRelease>::const_iterator ThisRelease=Releases.begin();
			while (ThisRelease!=Releases.end())
			{
				MusicBrainz4::CRelease Release=*ThisRelease;

				WaitRequest();
				MusicBrainz4::CRelease FullRelease=MusicBrainz.LookupRelease(Release.ID());

				std::vector<MusicBrainz4::CMedium> Media=FullRelease.MediaMatchingDiscID(DiskID);
				std::vector<MusicBrainz4::CMedium>::const_iterator ThisMedium=Media.begin();
				while (ThisMedium!=Media.end())
				{
					MusicBrainz4::CMedium Medium=*ThisMedium;

					if (FullRelease.ReleaseGroup() || !FullRelease.ReleaseGroup()->Title().empty())
						std::cout << "Album name: " << FullRelease.ReleaseGroup()->Title() << std::endl;
					else
						std::cout << "Album name: " << FullRelease.Title() << std::endl;

					if (FullRelease.MediumList() && FullRelease.MediumList()->Items().size()>1)
						std::cout << "Disk number: " << Medium.Position() << std::endl;

					std::cout << "AlbumID: " << FullRelease.ID() << std::endl;

					std::string ArtistName;
					std::string ArtistSort;

					bool FirstArtist=true;
					MusicBrainz4::CArtistCredit *ArtistCredit=FullRelease.ArtistCredit();
					if (ArtistCredit)
					{
						std::vector<MusicBrainz4::CNameCredit> NameCredits=ArtistCredit->NameCredits();
						std::vector<MusicBrainz4::CNameCredit>::const_iterator ThisNameCredit=NameCredits.begin();
						while (ThisNameCredit!=NameCredits.end())
						{
							MusicBrainz4::CNameCredit NameCredit=*ThisNameCredit;
							MusicBrainz4::CArtist *Artist=NameCredit.Artist();

							if (!NameCredit.Name().empty())
								ArtistName+=NameCredit.Name();
							else if (Artist)
								ArtistName+=Artist->Name();

							ArtistName+=NameCredit.JoinPhrase();

							if (Artist)
							{
								ArtistSort+=Artist->SortName();
								ArtistSort+=NameCredit.JoinPhrase();
							}


							if (FirstArtist)
							{
								FirstArtist=false;
								if (Artist)
									std::cout << "ArtistID: " << Artist->ID() << std::endl;
							}

							++ThisNameCredit;
						}

						std::cout << "Artist: " << ArtistName << std::endl;
						std::cout << "ArtistSort: " << ArtistSort << std::endl;
					}

					std::cout << "ASIN: " << FullRelease.ASIN() << std::endl;

					if (!FullRelease.ASIN().empty())
					{
						std::string URL="/images/P/" + FullRelease.ASIN() + ".02.LZZZZZZZ.jpg";

						CHTTPFetch Fetch("images.amazon.com");

						int Bytes=Fetch.Fetch(URL);
						if (Bytes<1000)
						{
							URL="/images/P/" + FullRelease.ASIN() + ".02.MZZZZZZZ.jpg";
							Bytes=Fetch.Fetch(URL);
						}

						if (Bytes>0)
						{
							if (Bytes<1000)
								std::cout << "Album art downloaded was less than 1000 bytes, ignoring" << std::endl;
							else
							{
								std::vector<unsigned char> Data=Fetch.Data();
								std::cout << "Got cover art" << std::endl;
							}
						}
						else
							std::cout << "Error downloading art: " + Fetch.ErrorMessage() << std::endl;
					}

					if (FullRelease.ReleaseGroup())
							std::cout << "Type: " << AlbumType(FullRelease.ReleaseGroup()->Type()) << std::endl;

					std::cout << "Status: " << AlbumStatus(FullRelease.Status()) << std::endl;

					MusicBrainz4::CGenericList<MusicBrainz4::CTrack> *TrackList=Medium.TrackList();
					if (TrackList)
					{
						std::vector<MusicBrainz4::CTrack> Tracks=TrackList->Items();
						std::vector<MusicBrainz4::CTrack>::const_iterator ThisTrack=Tracks.begin();
						while (ThisTrack!=Tracks.end())
						{
							MusicBrainz4::CTrack MBTrack=*ThisTrack;

							std::cout << std::endl << "TrackNumber: " << MBTrack.Position() << std::endl;

							if (!MBTrack.Title().empty())
								std::cout << "TrackName: " << MBTrack.Title() << std::endl;
							else if (MBTrack.Recording())
								std::cout << "TrackName: " << MBTrack.Recording()->Title() << std::endl;

							std::string ArtistName;
							std::string ArtistSort;

							bool FirstArtist=true;
							if (MBTrack.Recording())
							{
								MusicBrainz4::CArtistCredit *ArtistCredit=MBTrack.Recording()->ArtistCredit();
								if (ArtistCredit)
								{
									std::vector<MusicBrainz4::CNameCredit> NameCredits=ArtistCredit->NameCredits();
									std::vector<MusicBrainz4::CNameCredit>::const_iterator ThisNameCredit=NameCredits.begin();
									while (ThisNameCredit!=NameCredits.end())
									{
										MusicBrainz4::CNameCredit NameCredit=*ThisNameCredit;
										MusicBrainz4::CArtist *Artist=NameCredit.Artist();

										if (!NameCredit.Name().empty())
											ArtistName+=NameCredit.Name();
										else if (Artist)
											ArtistName+=Artist->Name();

										ArtistName+=NameCredit.JoinPhrase();

										if (Artist)
										{
											ArtistSort+=Artist->SortName();
											ArtistSort+=NameCredit.JoinPhrase();
										}

										if (FirstArtist)
										{
											FirstArtist=false;
											if (Artist)
												std::cout << "TrackArtistID: " << Artist->ID() << std::endl;
										}

										++ThisNameCredit;
									}
								}
							}

							std::cout << "TrackArtist: " << ArtistName << std::endl;
							std::cout << "TrackArtistSort: " << ArtistSort << std::endl;

							if (MBTrack.Recording())
								std::cout << "TrackID: " << MBTrack.Recording()->ID() << std::endl;

							++ThisTrack;
						}
					}

					std::string AlbumDate=FullRelease.Date();

					std::string::size_type MinusPos=AlbumDate.find("-");
					if (std::string::npos!=MinusPos)
						AlbumDate=AlbumDate.substr(0,MinusPos);

					std::cout << "Date: " << AlbumDate << std::endl;

					++ThisMedium;
				}

				++ThisRelease;
			}
		}
		else
		{
			std::cout << "No albums found for DiscID << '" << DiskID << "'" << std::endl;
		}

		++ThisID;
	}
}

std::string AlbumType(const std::string Type)
{
	const char *AlbumTypeStrings[] =
	{
		"album", "single", "EP", "compilation", "soundtrack",
		"spokenword", "interview", "audiobook", "live", "remix", "other", "\0"
	};

	std::string Ret;

	int i=0;

	while (AlbumTypeStrings[i][0]!='\0')
	{
		if (strcasecmp(Type.c_str(),AlbumTypeStrings[i])==0)
		{
			Ret=AlbumTypeStrings[i];
			break;
		}

		++i;
	}

	return Ret;
}

std::string AlbumStatus(const std::string Status)
{
	const char *AlbumStatusStrings[] =
	{
		"official", "promotion", "bootleg", "\0"
	};

	std::string Ret;

	int i=0;

	while (AlbumStatusStrings[i][0]!='\0')
	{
		if (strcasecmp(Status.c_str(),AlbumStatusStrings[i])==0)
		{
			Ret=AlbumStatusStrings[i];
			break;
		}

		++i;
	}

	return Ret;
}

void WaitRequest()
{
	static time_t LastRequest=0;
	const time_t TimeBetweenRequests=2;

	time_t TimeNow;

	do
	{
		TimeNow=time(NULL);
		if (abs(TimeNow-LastRequest)<TimeBetweenRequests)
			usleep(100000);
	}	while (abs(TimeNow-LastRequest)<TimeBetweenRequests);

	LastRequest=TimeNow;
}
