#include <iostream>
#include <vector>

class Point
{
private:
	int m_x{};
	int m_y{};

public:
	Point( int x, int y ) :m_x{ x }, m_y{ y }{}

	friend std::ostream& operator<<( std::ostream& out, const Point& point )
	{
		std::cout << "Point(" << point.m_x << ", " << point.m_y << ")";
		return out;
	}
};

class Shape
{
public:

	virtual ~Shape( ) {};

	virtual std::ostream& print( std::ostream& out ) const = 0;

	friend std::ostream& operator<<( std::ostream& out, const Shape& shape )
	{
		return shape.print( out );
	}
};

class Triangle :public Shape
{
private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
public:
	Triangle( Point p1, Point p2, Point p3 ) :m_p1{ p1 }, m_p2{ p2 }, m_p3{ p3 }{}

	std::ostream& print( std::ostream& out ) const override
	{
		out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ")";
		return out;
	}
};

class Circle :public Shape
{
private:
	Point m_point;
	int m_radius{};

public:
	Circle( Point point, int radius ) :m_point{ point }, m_radius{ radius }{}

	std::ostream& print( std::ostream& out ) const override
	{
		out << "Circle(" << m_point << ", radius " << m_radius  << ")";
		return out;
	}

	int getRadius( Shape* shape )
	{
		Circle* circle{ dynamic_cast<Circle*>(shape) };

		if ( circle )
			return circle->m_radius;
		else
			return 0;
	}
};

int getLargestRadius( const std::vector<Shape*>& vecky )
{
	Circle* circle{};
	int radius{0};
	for ( Shape* shape : vecky )
	{
		if ( circle->getRadius( shape ) > radius )
			radius = circle->getRadius( shape );
	}

	return radius;
}

int main()
{
	std::vector<Shape*> v{
	  new Circle{Point{ 1, 2 }, 7},
	  new Triangle{Point{ 1, 2 }, Point{ 3, 4 }, Point{ 5, 6 }},
	  new Circle{Point{ 7, 8 }, 22}
	};

	for ( Shape* shape : v )
	{
		std::cout << *shape << '\n';
	}

	std::cout << "The largest radius is: " << getLargestRadius( v ) << '\n';

	for ( Shape* shape : v )
	{
		delete shape;
	}

    return 0;
}