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
    b = abs(b);
    while(a < 0) {
        a += b;
    }
    if(a == 0 || b == 0 || !isCoprime(a, b)) {
        return 0;
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

std::vector<std::vector<int>> reduceM(std::vector<std::vector<int>> M, int x, int y){
    M.erase(M.begin() + y);
    for(int i = 0; i < M.size(); i++) {
        M[i].erase(M[i].begin() + x);
    }
    return M;
}

int det(std::vector<std::vector<int>> b) {
    int sum = 0;
    int L = 0;
    if(b.size() == 0) {
        return 1;
    }
    for(int i = 0; i < b.size(); i++){
        if(b[i].size() != b.size()) {
            return 0;
        }
        if(avg(b[L]) > avg(b[i])) {
            L = i;
        }
    }
    for(int i = 0; i < b[L].size(); i++){
        // dubious
        int c = b[L][i];
        std::vector<std::vector<int>> s = b;
        // s.erase(s.begin() + L);
        // for(int j = 0; j < s.size(); j++) {
        //     s[j].erase(s[j].begin() + i);
        // }
        // pow?
        sum += pow(-1, i)*c*det(reduceM(s, i, L));
    }
    return sum;
}

std::vector<std::vector<int>> invM(std::vector<std::vector<int>> M, int b){
    for(int i = 0; i < M.size(); i++){
        if(M[i].size() != M.size()){
            return {{}};
        }
    }
    // if(det(M) % b == 0) {
    //     return {{}};
    // }
    int mP = inv(det(M), b);
    if(mP == 0) {
        return {{}};
    }
    std::vector<std::vector<int>> r;
    
    for(int i = 0; i < M.size(); i++){
        r.push_back(std::vector<int>());
        for(int j = 0; j < M[i].size(); j++){
            int cell = pow(-1, (i+j)%2) * det(reduceM(M, i, j)) * mP;
            cell %= b;
            while(cell < 0) {
                cell += b;
            }
            r[i].push_back(cell);
        }
    }
    return r;
}

std::vector<int> applyMatrix(std::vector<int> c, std::vector<std::vector<int>> M, int b) {
    std::vector<int> r;
    for(int i = 0; i < M.size(); i++) {
        int sum = 0;
        for(int j = 0; j < M[i].size(); j++) {
            sum += M[i][j] * c[j];
        }
        while(sum < 0){
            sum += b;
        }
        r.push_back(sum%b);
    }
    return r;
}

int B = 5;

int main() {
    // does it really work?
    // sample tests with solving lights out then... assuming congruent data is fitted inside
    std::vector<std::vector<int>> a;
    for(int i = 0; i < pow(B, 2); i++) {
        std::vector<int> r;
        for(int j = 0; j < pow(B, 2); j++) {
            int d = 0;
            if(abs((j-i)%B) <= 1 || abs(j-i) == 5) {
                d = 1;
            }
            r.push_back(d);
        }
        a.push_back(r);
    }
    std::vector<std::vector<int>> s = invM(a, 2);
    std::vector<int> difference = {0, 1, 1, 1, 1,
                                   1, 1, 0, 0, 1,
                                   0, 0, 0, 0, 1,
                                   0, 1, 0, 0, 0,
                                   0, 1, 1, 0, 1
    };
    std::vector<int> solution = applyMatrix(difference, s, 2);
    // for(int i = 0; i < s.size(); i++) {
    //     for(int j = 0; j < s[i].size(); j++) {
    //         std::cout << s[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    for(int i = 0; i < solution.size(); i++) {
        std::cout << solution[i] << " ";
    }
    return 0;
}
