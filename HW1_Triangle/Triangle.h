/*
 * Triangle.h
 *
 *  Created on: 2020. 9. 5.
 *  Author: jimin
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include <math.h>

struct Point {
	int x;
	int y;
};

class Triangle{
private:
	Point p1;
	Point p2;
	Point p3;
public:
	Triangle(const Point& p1, const Point& p2, const Point& p3){ // Triangle ������
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
	}
	double area(){	// �ﰢ���� ������ ���ϴ� �޼ҵ�

		/*
		 * <�� ��ǥ�� �̿��� �ﰢ�� ���� ����>
		 *
		 * 1. p1�� p2 ���� ���� ���ϱ�(�غ�)
		 * 2. p1, p2�� ������ ���� ������ ���ϱ�
		 * 3. p3�� ���������� ������ �Ÿ� ���ϱ�(����)
		 * 4. ���� = �غ� * ���� / 2
		 * => ���� S = 1/2 * |(x1 - x2)y3 + (x2 - x3)y1 + (x3 - x1)y2|
		 */

		return fabs((p1.x - p2.x) * p3.y + (p2.x - p3.x) * p1.y + (p3.x - p1.x) * p2.y) / 2.0;
	}
	bool isInside(const Point& p){	// ����� ����, �ܺ� �Ǵ� �޼ҵ�(true == ����, false == �ܺ�)

		// p1, p2�� ���������Ŀ��� p3�� p�� ���� ��
		if(equation(p1, p2, p3) == equation(p1, p2, p))
			// p2, p3�� ���������Ŀ��� p1�� p�� ���� ��
			if(equation(p2, p3, p1) == equation(p2, p3, p))
				// p1, p3�� ���������Ŀ��� p1�� p�� ���� ��
				if(equation(p1, p3, p2) == equation(p1, p3, p))
					return true;

		return false;
	}
	//��ǥ pa, pb�� ���������Ŀ��� p�� ���� ����
	int equation(const Point pa, const Point pb, const Point p){
		// ���� ������ (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1) = 0
		double domain = (p.x - pa.x) * (pb.y - pa.y) - (p.y - pa.y) * (pb.x - pa.x);

		if (domain == 0) {
			std::cout << "���� \n";
			exit(0);
		}
		if(domain > 0) return 1;
		else if(domain < 0) return -1;

	}
};



#endif /* TRIANGLE_H_ */
