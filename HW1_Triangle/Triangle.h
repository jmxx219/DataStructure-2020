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
	Triangle(const Point& p1, const Point& p2, const Point& p3){ // Triangle 생성자
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
	}
	double area(){	// 삼각형의 면적을 구하는 메소드

		/*
		 * <세 좌표를 이용한 삼각형 넓이 공식>
		 *
		 * 1. p1과 p2 선분 길이 구하기(밑변)
		 * 2. p1, p2를 지나는 직선 방정식 구하기
		 * 3. p3와 직선방정식 사이의 거리 구하기(높이)
		 * 4. 넓이 = 밑변 * 높이 / 2
		 * => 공식 S = 1/2 * |(x1 - x2)y3 + (x2 - x3)y1 + (x3 - x1)y2|
		 */

		return fabs((p1.x - p2.x) * p3.y + (p2.x - p3.x) * p1.y + (p3.x - p1.x) * p2.y) / 2.0;
	}
	bool isInside(const Point& p){	// 삼격형 내부, 외부 판단 메소드(true == 내부, false == 외부)

		// p1, p2의 직선방정식에서 p3와 p의 영역 비교
		if(equation(p1, p2, p3) == equation(p1, p2, p))
			// p2, p3의 직선방정식에서 p1와 p의 영역 비교
			if(equation(p2, p3, p1) == equation(p2, p3, p))
				// p1, p3의 직선방정식에서 p1와 p의 영역 비교
				if(equation(p1, p3, p2) == equation(p1, p3, p))
					return true;

		return false;
	}
	//좌표 pa, pb의 직선방정식에서 p가 속한 영역
	int equation(const Point pa, const Point pb, const Point p){
		// 직선 방정식 (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1) = 0
		double domain = (p.x - pa.x) * (pb.y - pa.y) - (p.y - pa.y) * (pb.x - pa.x);

		if (domain == 0) {
			std::cout << "내부 \n";
			exit(0);
		}
		if(domain > 0) return 1;
		else if(domain < 0) return -1;

	}
};



#endif /* TRIANGLE_H_ */
