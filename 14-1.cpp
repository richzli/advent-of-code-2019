#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <list>
using namespace std;

#define pis pair<int, string>

map<string, pair<int, vector<pis>>> reactions;

int main() {
    while (true) {
        string in;
        getline(cin, in);

        if (in == "END") {
            break;
        }

        vector<pis> reactants;
        int i;
        while ((i = in.find(',')) != string::npos) {
            string reactant = in.substr(0, i);
            int q;
            char label[10];
            sscanf(&reactant[0], "%d %s", &q, label);
            string rr = label;
            reactants.push_back(pis(q, rr));
            in.erase(0, i+2);
            std::cout << q << " " << rr << ", ";
        }

        int q1, q2;
        char labell[10], productt[10];
        sscanf(&in[0], "%d %s => %d %s", &q1, labell, &q2, productt);
        string label = labell, product = productt;
        reactants.push_back(pis(q1, label));
        reactions.insert(pair<string, pair<int, vector<pis>>>(product, pair<int, vector<pis>>(q2, reactants)));
        std::cout << q1 << " " << label << " MAKES " << q2 << " " << product << endl;
    }

    std::cout << endl;

    list<pis> queue;
    queue.push_back(pis(1, "FUEL"));
    map<string, int> leftover;

    int ores = 0;

    while (queue.size() > 0) {
        pis r = queue.front();
        queue.pop_front();

        if (r.second == "ORE") {
            std::cout << "USING " << r.first << " ORE" << endl;
            ores += r.first;
        } else {
            std::cout << "CREATING " << r.first << " " << r.second << ":" << endl;
            auto it = leftover.find(r.second);
            if (it != leftover.end()) {
                std::cout << " - USING LEFTOVERS" << endl;
                if (it->second > r.first) {
                    it->second -= r.first;
                    continue;
                } else if (it->second == r.first) {
                    leftover.erase(it);
                    continue;
                } else {
                    r.first -= it->second;
                    leftover.erase(it);
                }
            }

            std::cout << " - " << r.first << " " << r.second << " REMAINS" << endl;

            auto rxn = reactions.find(r.second);
            int rxns = 1 + (r.first - 1) / rxn->second.first;
            std::cout << " - " << rxns << " RXNS REQUIRED, MAKING " << rxn->second.first << " EACH TIME" << endl;

            for (pis reactant : rxn->second.second) {
                pis rrr(reactant.first * rxns, reactant.second);
                std::cout << " - REQUIRES " << rrr.first << " " << rrr.second << endl;
                queue.push_back(rrr);
            }
            
            int leftovers = rxns * rxn->second.first - r.first;
            std::cout << " - HAD " << leftovers << " LEFTOVER" << endl;
            leftover.insert(pair<string, int>(r.second, leftovers));
        }
    }

    std::cout << "ORES NEEDED: " << ores;
    return 0;
}