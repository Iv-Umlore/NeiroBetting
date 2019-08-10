#include <vector>
#include <fstream>

#include "Network.h"

using namespace std;


int main() {

	cout << "Study or Prdiction? S\\P" << endl;
	char answer;
	Network NW;
	string way;
	
	cin >> answer;
	//vector<double> vect;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			double tmp = GetAlternateMatchRate(i, j);
			cout << i << " : " << j << " - " << tmp << endl;
			//vect.push_back(tmp);
		}
	
	/*std::sort(vect.rbegin(), vect.rend());
	for (int i = 0; i < 100; i++)
		cout << vect[i] << endl;*/

	if (answer == 'S') {
		vector<Match> matches = ReadAllMatches();		
		cout << "Tests count = " << matches.size() << endl;
		int count;
		cout << "Circle count?\n";
		cin >> count;
		NW.VangaLerning(matches, count); /*matches[i].lastResults, matches[i].CorrectResult*/	// учим

	}
	else if (answer == 'P') {
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\results.txt";
		ifstream in(way);
		Match testMatch(in);
		NW.Vanga(testMatch.lastResults);		// просим результат
		PrintMatchPrediction(NW.GetPrediction());
	}
	else cout << "Sorry, u write full trash!" << endl;	

	cout << "\a\a\a\a";
	system("pause");
	return 0;
}