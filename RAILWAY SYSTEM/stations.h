#pragma once



struct stationDATA{
	string name;
	sf::Vector2f relative_position;
	vector<stationDATA*> links;

	stationDATA(const string& name, sf::Vector2f p, vector<stationDATA*> l):
	name(name), relative_position(p),links(l){}

	stationDATA(const string& name, sf::Vector2f p) :
		name(name), relative_position(p){}

	stationDATA() {

	}

	void addlink(stationDATA* l) {
		
			links.push_back(l);
		
	}
};


class graph {
public:
	int stations;
	vector<vector<int>> adjacency_matrix;
	unordered_map<string, int> nameofindex;

	graph() {
		/*stations = 4;
		nameofindex.insert({ "anas", 0 });
		nameofindex.insert({ "khan", 1 });
		nameofindex.insert({ "ali", 2 });
		nameofindex.insert({ "feroz", 3 });

		adjacency_matrix.resize(4, vector<int>(4, 0));*/

		stations = 18;
		nameofindex.insert({ "maplewood", 0 });
		nameofindex.insert({ "riverside", 1 });
		nameofindex.insert({ "westend", 2 });
		nameofindex.insert({ "oceanfront", 3 });
		nameofindex.insert({ "pinecrest", 4 });
		nameofindex.insert({ "hillcrest", 5 });
		nameofindex.insert({ "park", 6 });
		nameofindex.insert({ "elm", 7 });
		nameofindex.insert({ "cent", 8 });
		nameofindex.insert({ "hbr", 9 });
		nameofindex.insert({ "hlcrst", 10 });
		nameofindex.insert({ "sntst", 11 });
		nameofindex.insert({ "view", 12 });
		nameofindex.insert({ "end", 13 });
		nameofindex.insert({ "valley", 14 });
		nameofindex.insert({ "profammar", 15 });
		nameofindex.insert({ "profayan", 16 });
		nameofindex.insert({ "profanas", 17 });

		adjacency_matrix.resize(18, vector<int>(18, 0));
	}

	void defaultset(const stationDATA& a) {
		
		for (const auto& linkedStation : a.links) {
			if (nameofindex.find(linkedStation->name) != nameofindex.end()) {
				int indexA = nameofindex[a.name];
				int indexB = nameofindex[linkedStation->name];
				float temp = distanceBetweenPoints(a.relative_position, linkedStation->relative_position);
				adjacency_matrix[indexA][indexB] = temp;
				adjacency_matrix[indexB][indexA] = temp; 
			}
		}
	}

	float distanceBetweenPoints(const sf::Vector2f& p1, const sf::Vector2f& p2) {
		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;

		return sqrt(dx * dx + dy * dy);
	}


	bool doesExist(string a) {
		auto it = nameofindex.find(a);
		if (it != nameofindex.end()) {
			return false;
		}
			return true;
		
	}

	void addstation(const stationDATA& a) {
		nameofindex.insert({ a.name, stations });
		stations++;

		for (auto& row : adjacency_matrix) {
			row.resize(stations, 0);
		}

		adjacency_matrix.emplace_back(stations, 0);

		defaultset(a);
	}

	void print() {
		for (size_t i = 0; i < stations; i++)
		{
			for (size_t j = 0; j < stations; j++)
			{
				cout << adjacency_matrix[i][j] << "  ";
			}
			cout << endl;
		}
	}

	void removestation(const string& stationName) {
		auto iter = nameofindex.find(stationName);
		if (iter != nameofindex.end()) {
			int stationIndex = iter->second;

			nameofindex.erase(iter);

			for (size_t i = 0; i < stations; ++i) {
				adjacency_matrix[i].erase(adjacency_matrix[i].begin() + stationIndex);
			}
			adjacency_matrix.erase(adjacency_matrix.begin() + stationIndex);

			for (auto& pair : nameofindex) {
				if (pair.second > stationIndex) {
					pair.second--;
				}
			}

			stations--; 
		}
	}

		




};