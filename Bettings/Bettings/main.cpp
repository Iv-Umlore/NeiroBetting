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