#include <iostream>
#include <vector>
#include <fstream>

#include "Network.h"
#include "Match.h"

using namespace std;

int main() {

	cout << "Study or Prdiction? S\\P" << endl;
	char answer;
	cin >> answer;
	Network NW;
	string way;
	if (answer == 'S') {
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\USA_USL_ChampShip.txt";
		ifstream in(way);
		int count;
		int balls1, balls2;
		in >> count;
		Match* matches = new Match[count];
		for (int i = 0; i < count; i++) {
			matches[i] = Match(in);
			in >> balls1 >> balls2;
			matches[i].SetMatchResult(balls1, balls2);
		}
		for (int i = 0; i < count; i++)
			NW.VangaLerning(matches[i].lastResults, matches[i].CorrectResult);	// учим
	}
	else if (answer == 'P') {
		way = "D:\\PROGRAMS\\NeiroBetting\\Bettings\\results.txt";
		ifstream in(way);
		Match testMatch(in);
		NW.Vanga(testMatch.lastResults);		// просим результат
	}
	else cout << "Sorry, u write full trash!" << endl;	
	
	
	system("pause");
	return 0;
}