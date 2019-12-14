#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <list>
using namespace std;

#define pis pair<long long, string>

map<string, pair<long long, vector<pis>>> reactions;

long long make(int amt) {
    list<pis> queue;
    queue.push_back(pis(amt, "FUEL"));
    map<string, long long> leftover;

    long long ores = 0;

    while (queue.size() > 0) {
        pis r = queue.front();
        queue.pop_front();

        if (r.second == "ORE") {
            ores += r.first;
        } else {
            auto it = leftover.find(r.second);
            if (it != leftover.end()) {
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

            auto rxn = reactions.find(r.second);
            long long rxns = 1 + (r.first - 1) / rxn->second.first;

            for (pis reactant : rxn->second.second) {
                pis rrr(reactant.first * rxns, reactant.second);
                queue.push_back(rrr);
            }
            
            long long leftovers = rxns * rxn->second.first - r.first;
            leftover.insert(pair<string, int>(r.second, leftovers));
        }
    }

    return ores;
}

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
            // std::cout << q << " " << rr << ", ";
        }

        int q1, q2;
        char labell[10], productt[10];
        sscanf(&in[0], "%d %s => %d %s", &q1, labell, &q2, productt);
        string label = labell, product = productt;
        reactants.push_back(pis(q1, label));
        reactions.insert(pair<string, pair<int, vector<pis>>>(product, pair<int, vector<pis>>(q2, reactants)));
        // std::cout << q1 << " " << label << " MAKES " << q2 << " " << product << endl;
    }

    int lower = 3817376, upper = 5000000;

    while (upper != lower) {
        int mid = (lower+upper)/2;
        // cout << "low: " << lower << " mid: " << mid << " high: " << upper << endl;
        long long m = make(mid);
        // cout << "make: " << m << endl;
        if (m < 1000000000000ll) {
            if (lower == mid) {
                if (make(mid+1) < 1000000000000ll) {
                    lower = mid+1;
                } else {
                    upper = mid;
                }
            } else {
                lower = mid;
            }
        } else {
            upper = mid;
        }
    }
    
    cout << lower;

    return 0;
}