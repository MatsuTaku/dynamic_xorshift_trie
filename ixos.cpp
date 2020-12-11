#include <iostream>
#include<vector>
#include<algorithm>
#include <math.h>
#include <sstream>

static constexpr uint64_t default_size = std::pow(2,24);
std::vector<int> B_ = {13,-7,5};//ビットシフトパターン
int k = (std::log(default_size)/std::log(2))+8;//mask値の決定のため、P, C 拡張時にインクリメント

uint64_t xos(uint64_t x){//前&x
    uint64_t maskXos_ = (1 << k);
	for(int b: B_){//ビットシフトパターン{a,b}なら先にa次にbの２回ループ
        //std::cout << "shift patern , seed" << b << "," << x << "\n";
		if(b >= 0){
			x = (x ^ (x << b)) % maskXos_;
		}
		else if(b < 0){
			x = (x ^ (x >> -b)) % maskXos_;
        }
	}
	std::cout << "output :" << x << "\n";
	return x;
}

uint64_t ixos(uint64_t x){//前&x
    uint64_t maskXos_ = (1 << k);
	for(int b: B_){//ビットシフトパターン{a,b}なら先にa次にbの２回ループ
        //std::cout << "shift patern , seed" << b << "," << x << "\n";
		if(k % b == 0){
			if(b >= 0){
				for(int i = 0;i < (k/b); i++){
					x = (x ^ (x << b)) % maskXos_;
				}		
			}
			else if(b < 0){
				for(int i = 0;i < (k/-b); i++){
					x = (x ^ (x >> -b)) % maskXos_;
				}
			}
		}
		else{
			if(b >= 0){
				for(int i = 0;i < (k/b) + 1; i++){
					x = (x ^ (x << b)) % maskXos_;
				}		
			}
			else if(b < 0){
				for(int i = 0;i < (k/-b)-1; i++){
					x = (x ^ (x >> -b)) % maskXos_;
				}
			}
			std::cout << "seed B" << b << "  " << x << "\n";
		}

		std::cout << "seed" << x << "\n";
	}
	return x;
} 

int main(){
    uint64_t seed = 98;
    uint64_t x = xos(seed);//シード値→出力値
    uint64_t s1 = ixos(x);//出力値→シード値
    return 0;
}


 