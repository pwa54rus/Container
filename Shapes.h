class Shape : public Printable{

public:
    static int getCount(){

        return Shape::counter;
	}

    Shape(){

        ++Shape::counter;
	}

    virtual ~Shape(){

        --Shape::counter;
	}

    virtual void randomInitialisation() = 0;

private:
    static int counter;

};

int Shape::counter = 0;

std::ostream & operator << ( std::ostream & stream, Shape const & shape ){

    return stream << shape.print();
}


class Point : public Named, public Shape
{
public:
    std::string print() const override{

        return "\n=====\n("
               + Named::print() + ")\n"
               + "X - " + std::to_string(x) + "\n"
               + "Y - " + std::to_string(y);
	}

    void randomInitialisation() override{

        x = 1+ rand() % 10;
        y = 1+ rand() % 10;
	}

    double getDistanceBetweenPoints( Point const & point ){

        return sqrt( pow( x - point.x, 2 ) + pow( y - point.y, 2 ) );
	}

	Point() : Named( "Point" )
	{}

    Point( double x1, double y1 ) : Point(){
        x = x1;
        y = y1;
	}

    Point( Point const & point ) : Point( point.x, point.y )
	{}

    double x;
    double y;
};


class Rect : public Named, public Shape{

public:
    Point leftBottom;
    Point rightTop;


    std::string print() const override{

        return "\n=====\n("
               + Named::print() + ")\n"
               + "Square = " + std::to_string( getSquare() ) + "\n"
               + "Perimeter = " + std::to_string( getPerimeter() ) + "\n"
               + "LeftBottom = " + leftBottom.print() + "\n"
               + "RightTop = " + rightTop.print() + "\n";
	}

    void randomInitialisation() override{

        int x1 = rand() % 10 + 1;
        int x2 = rand() % 10 + 1;
        int y1 = rand() % 10 + 1;
        int y2 = rand() % 10 + 1;

        leftBottom = Point(fmin( x1, x2 ),fmin( y1, y2 ));

        rightTop = Point(fmax( x1, x2 ),fmax( y1, y2 ));

	}

    double getWidth() const{

        return rightTop.x - leftBottom.x;
    }

    double getHeight() const{

        return rightTop.y - leftBottom.y;
    }

    double getSquare() const{

        return getWidth() * getHeight();
	}

    double getPerimeter() const{

        return 2 * ( getWidth() + getHeight() );
	}



	Rect() : Named( "Rect" )
	{}

	Rect( double x1, double y1, double x2, double y2 )
        : Named( "Rect" ), leftBottom( fmin( x1, x2 ), fmin( y1, y2 ) )
		, rightTop( fmax( x1, x2 ), fmax( y1, y2 ) )

	{}

    Rect( Point const & first, Point const & second )
        : Rect( first.x, first.y, second.x, second.y )
	{}


};


class Square : public Rect
{
public:
    virtual void randomInitialisation(){

        leftBottom.randomInitialisation();

        double width = 1+ rand() % 10;

        rightTop.x = leftBottom.x + width;
        rightTop.y = leftBottom.y + width;
	}

    Square(){

        name = "Square";
	}

	Square( double x, double y, double width )
        : Rect( x, y, x + width, y + width ){

        name = "Square";
	}

    Square( Point const & leftBottom, double width )
        : Square ( leftBottom.x, leftBottom.y, width )
	{}
};


class Polyline : public Named, public Shape{

public:

    Container< Point > points;

    std::string print() const override{

        std::string result = "\n=====\n(" + Named::print() + ")\n";


        Container< Point >::Item * iterator = points.first;
        while ( iterator->next ){

            result += iterator->data.print() + "\n";
            iterator = iterator->next;
		}
        result += iterator->data.print() + "\n";
        result += "length = " + std::to_string( getLength() );
		return result;
	}

    void randomInitialisation() override{

        int size = 1 + rand() % 10;

        for ( int i = 0; i < size; ++i ){

            Point point;
            point.randomInitialisation();
            points.putLast( point );
		}
	}


    virtual double getLength() const{

		double length = 0;

        Container< Point >::Item * iterator = points.first;
        Container< Point >::Item * next;
        while ( iterator->next ){

            next = iterator->next;
            length += iterator->data.getDistanceBetweenPoints( next->data );
            iterator = next;
		}
		return length;
	}

	Polyline()
        : Named( "Polyline" ), points()
	{}

    Polyline( Point const & point ) : Polyline(){

        points.putLast( point );
	}


};


class Polygon : public Polyline
{
public:
    virtual double getLength() const{

        return Polyline::getLength() + points.getFirst().getDistanceBetweenPoints( points.getLast() );
	}

    Polygon() : Polyline(){

        name = "Polygon";
	}

    Polygon( Point const & point ) : Polyline( point ){

        name = "Polygon";
	}
};

class Circle : public Named, public Shape{

public:
    Point center;
    double radius;


    std::string print() const override{

        return "\n=====\n("
               + Named::print() + ")\n"
               + "Radius - " + std::to_string( radius ) + "\n"
               + "Center - " + center.print() + "\n"
               + "Square - " + std::to_string( getSquare() ) + "\n"
               + "Length - " + std::to_string( getLength() );
    }

    void randomInitialisation() override{

        center.randomInitialisation();
        radius = 1 + rand() % 10;
    }

    double getSquare() const{

        return 3.1415 * pow( radius, 2 );
    }

    double getLength() const{

        return 3.1415 * 2 * radius;
    }

    Circle() : Named( "Cirlce" )
    {}

    Circle( Point center, double radius ): Named( "Cirlce" ), center( center ), radius( abs( radius ) )
    {}

};

