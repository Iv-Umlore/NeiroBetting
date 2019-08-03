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
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\USA.txt";
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

		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\Russia.txt";
		in.open(way);
		in >> count;
		MatchCount = matches.size();
		for (int i = MatchCount; i < count + MatchCount; i++) {
			matches.push_back(Match(in));
			in >> balls1 >> balls2;
			matches[i].SetMatchResult(balls1, balls2);
		}
		in.close();
		int* bester = new int[2];
		int* bester2 = new int[2];
		bester[0] = 0;
		bester[1] = 0;
		int barier = 0;
		double parametr = 0.1;
		double learningspeed = 1;
		cout << "Tests count = " << matches.size() << endl;
		//for (int OMG = 0; OMG < 10; OMG++) {
			for (int k = 0; k < 10; k++) {
				for (int j = 0; j < 100; j++)
					for (int i = 0; i < matches.size(); i++)
						NW.VangaLerning(matches[i].lastResults, matches[i].CorrectResult, learningspeed);	// учим
				cout << "Correct Result: " << NW.goodValue << endl;
				cout << "Errors: " << NW.numberofErrors  << "; Speed: "<< learningspeed <<  endl << endl;
				//system("pause");}
				if (k == 0) barier = NW.numberofErrors;
				if (NW.numberofErrors <= barier - NW.numberofErrors * 0.5) {
					barier = NW.numberofErrors;
					learningspeed += parametr;
				}
				if (NW.numberofErrors >= barier + NW.numberofErrors * 0.05) {
					barier = NW.numberofErrors;
					learningspeed -= parametr;
				}
				if (NW.numberofErrors > bester[0]) bester[0] = NW.numberofErrors;
				if (NW.goodValue > bester[1]) bester[1] = NW.goodValue;
				NW.numberofErrors = 0;
				NW.goodValue = 0;
			}
			cout /*<< "Circle number: " << OMG */<< " Bester closer Errors: " << bester[0] << " Bester good value: " << bester[1] << " Speed: " << learningspeed << endl;
			/*if (bester[0] > bester2[0]) bester2[0] = bester[0];
			if (bester[1] > bester2[1]) bester2[1] = bester[1];
			bester[0] = 0;
			bester[1] = 0;
		}*/

		/*cout << "\n\n Best of the best closer Errors: " << bester2[0] << "\n Best of the best good value: " << bester2[1]  << endl;*/

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
	cout << "Number of 'good' prediction: " << NW.goodValue << endl;

	system("pause");
	return 0;
}