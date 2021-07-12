#include <iostream>
#include "Triangle.h"

int main(){
	Point p1, p2, p3;

	std::cout << "�� ��ǥ�� �Է��ϼ���.\n";
	std::cout << "p1(x, y): "; std::cin >> p1.x >> p1.y;
	std::cout << "p2(x, y): "; std::cin >> p2.x >> p2.y;
	std::cout << "p3(x, y): "; std::cin >> p3.x >> p3.y;

	Triangle t(p1, p2, p3);
	std::cout<< "�ﰢ���� ����: " << t.area() << std::endl;

	Point p;
	std::cout << "\n��ǥ �Է�(px, py): "; std::cin >> p.x >> p.y;

	std::cout << "�ﰢ�� ���� �� �ܺ� �Ǻ�: ";
	if(t.isInside(p) == true) std::cout << "����\n";
	else std::cout << "�ܺ�\n";

	return 0;
}
