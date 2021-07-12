#include <iostream>
#include "Triangle.h"

int main(){
	Point p1, p2, p3;

	std::cout << "세 좌표를 입력하세요.\n";
	std::cout << "p1(x, y): "; std::cin >> p1.x >> p1.y;
	std::cout << "p2(x, y): "; std::cin >> p2.x >> p2.y;
	std::cout << "p3(x, y): "; std::cin >> p3.x >> p3.y;

	Triangle t(p1, p2, p3);
	std::cout<< "삼각형의 넓이: " << t.area() << std::endl;

	Point p;
	std::cout << "\n좌표 입력(px, py): "; std::cin >> p.x >> p.y;

	std::cout << "삼각형 내부 및 외부 판별: ";
	if(t.isInside(p) == true) std::cout << "내부\n";
	else std::cout << "외부\n";

	return 0;
}
