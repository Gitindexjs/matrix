// Online C++ compiler to run C++ program online
#include <iostream>
#include <vector>
#include <array>
#include <math.h>

std::vector<int> pFactors(int a) {
    std::vector<int> factors;
    for(int i = 2; i < sqrt(a); i++) {
        int seen = 0;
        for(int j = 0; j < factors.size()/2; j++) {
            if(i%factors[j*2]==0) {
                seen++;
            }
        }
        if(seen == 0) {
            int c = 0;
            while(a%i==0){
                c++;
                a/=i;
            }
            factors.push_back(i);
            factors.push_back(c);
        }
    }
    return factors;
}

bool isCoprime(int a, int b) {
    std::vector<int> pA = pFactors(a);
    std::vector<int> pB = pFactors(b);
    
    int s = pA.size();
    if(pB.size() < s) {
        s = pB.size();
    }
    for(int i = 0; i < s/2; i++) {
        if(!(pA[2*i+1] == 0 || pB[2*i+1] == 0)) {
            return 0;
        }
    }
    return 1;
}

int inv(int a, int b) {
    // erroneous flag
    if(a == 0 || b == 0 || !isCoprime(a, b)) {
        return 0;
    }
    b = abs(b);
    while(a < 0) {
        a += b;
    }
    int c = 1;
    while((c*a)%b != 1){
        c++;
    }
    return c;
}

int avg(std::vector<int> a) {
    int r = 0;
    for(int i = 0; i < a.size(); i++){
        r+= a[i];
    }
    return r/a.size();
}

int det(std::vector<std::vector<int>> b) {
    int sum = 0;
    int L = 0;
    for(int i = 0; i < b.size(); i++){
        if(b[i].size() != b.size()) {
            return 0;
        }
        if(avg(b[L]) >avg(b[i])) {
            L = i;
        }
    }
    for(int i = 0; i < b[L].size(); i++){
        // dubious
        int c = b[L][i];
        std::vector<std::vector<int>> s = b;
        s.erase(s.begin() + L);
        for(int j = 0; j < s.size(); j++) {
            s[j].erase(s[j].begin() + i);
        }
        // pow?
        sum += pow(-1, i)*c*det(s);
    }
    return sum;
}

int main() {
    std::cout << inv(-1, 2);
    std::vector<std::vector<int>> a = {{1}};
    std::cout << det(a);
    return 0;
}
