#include <iostream>
#include <math.h>
#include <string>
#include "Container.h"
#include "Base.h"
#include "Shapes.h"


int main()
{
    Container< Shape * > shapes;
    for( int i = 0; i < 20; ++i ){

        Shape * shape;

        switch( 1 + rand() % 6)
        {
            case 1:{

                shape = new Rect();
                break;
            }
            case 2:{

                shape = new Square();
                break;
            }
            case 3:{

                shape = new Polygon();
                break;
            }
            case 4:{

                shape = new Circle();
                break;
            }
            case 5:{

                shape = new Polyline();
                break;
            }
            case 6:{

                shape = new Point();
                break;
            }
            default:
                shape = new Point();
                break;
        }

        shape->randomInitialisation();

        shapes.putFirst( shape );
	}




    std::cout << "Number of shapes before cleaning - " << Shape::getCount() << std::endl;



    shapes.skipIterator();
    while( shapes.isNextExist() )
    {
        std::cout << * shapes.getIterated() << std::endl << std::endl;
        shapes.next();
    }


    while( !shapes.isEmpty() )
        {
            delete shapes.getLast();
            shapes.deleteLast();
        }



     std::cout << "Number of shapes after cleaning - " << Shape::getCount() << std::endl;

	return 0;
}

