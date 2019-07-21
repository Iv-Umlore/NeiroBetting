#include <vector>
#include <fstream>

#include "Network.h"
#include "Match.h"

using namespace std;

int main() {

	cout << "Study or Prdiction? S\\P" << endl;
	char answer;
	Network NW;
	string way;
	
	cin >> answer;
	
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			cout << i << " : " << j << " - " << GetMatchRate(i, j) << endl;
	
	if (answer == 'S') {
		vector<Match> matches;
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\USA_USL_ChampShip.txt";
		ifstream in(way);
		int count;
		int MatchCount;
		int balls1, balls2;
		in >> count;
		for (int i = 0; i < count; i++) {
			matches.push_back(Match(in));
			in >> balls1 >> balls2;
			matches[i].SetMatchResult(balls1, balls2);
		}
		in.close();

		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Japan.Best.txt";
		in.open(way);
		in >> count;
		MatchCount = matches.size();
		for (int i = MatchCount; i < count + MatchCount; i++) {
			matches.push_back(Match(in));
			in >> balls1 >> balls2;
			matches[i].SetMatchResult(balls1, balls2);
		}
		in.close();

		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Russia.Best.txt";
		in.open(way);
		in >> count;
		MatchCount = matches.size();
		for (int i = MatchCount; i < count + MatchCount; i++) {
			matches.push_back(Match(in));
			in >> balls1 >> balls2;
			matches[i].SetMatchResult(balls1, balls2);
		}
		in.close();

		int barier = 0;
		double learningspeed = 0.1;
		cout << "Tests count = " << matches.size() << endl;
		//for (int k = 0; k < 20; k++) {
			//for (int j = 0; j < 50; j++)
				for (int i = 0; i < matches.size(); i++)
					NW.VangaLerning(matches[i].lastResults, matches[i].CorrectResult, learningspeed);	// учим
			/*cout << "Circle nubber : " << k << "; Errors: " << NW.numberofErrors  << "; Speed: "<< learningspeed <<  endl;
			//system("pause");}
			if (k == 0) barier = NW.numberofErrors;
			if (NW.numberofErrors <= barier - NW.numberofErrors * 0.11) {
				barier  = NW.numberofErrors;
				learningspeed /= 0.9;
			}
			if (NW.numberofErrors >= barier + NW.numberofErrors * 0.09) {
				barier = NW.numberofErrors;
				learningspeed *= 0.9;
			}
			NW.numberofErrors = 0;
		}*/
	}
	else if (answer == 'P') {
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\results.txt";
		ifstream in(way);
		Match testMatch(in);
		NW.Vanga(testMatch.lastResults);		// просим результат
		PrintMatchPrediction(NW.GetPrediction());
	}
	else cout << "Sorry, u write full trash!" << endl;	
	
	cout << "Number of 'correct' prediction: " << NW.numberofErrors << endl;

	system("pause");
	return 0;
}