#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__
#include <iostream>

float randomFloat()
{
	float r = (float)rand() / (float)RAND_MAX;
	return r;
}

int predictOut(float weights[], float x, float y)
{
	float sum = x * weights[0] + y * weights[1] + weights[2];
	return (sum >= 0) ? 1 : -1;
}

class Point{
	public:
		float x_coord, y_coord;
		void set_points(float x, float y){
			x_coord = x;
			y_coord = y;
		}

		void print(){
			std::cout <<"(" << x_coord << "," << y_coord << ")" << std::endl;
		}

		friend Point operator+(Point a, Point b);


	private:
		//float x_coord, y_coord;
};

Point operator+(Point a, Point b){
			Point temp;
		   	temp.x_coord=b.x_coord+a.x_coord;
    		temp.y_coord=b.y_coord+a.y_coord;
    		return temp;
		}

std::ostream &operator<<(std::ostream &os, Point p){
	return os << "(" << p.x_coord << ", " << p.y_coord << ")";
} //takes a point and passes it to stream, ret stream
#endif//__ARITHMETIC_H__