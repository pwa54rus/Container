template< typename T > class Container{

public:
    T getIterated() const{

        return iterator->data;
    }

    bool isEmpty() const{

        return size == 0;
    }

    int getSize() const{

        return size;
    }

    T getFirst() const{

        return first->data;
    }

    T getLast() const{

        return last->data;
    }



    void deleteFirst(){

        if( !isEmpty() ){

            Item * temp = first;
            first = first->next;
            if ( first ){

                first->prev = nullptr;
            }
            delete temp;

            --size;
        }
        else{

            throw "there is no item to delete";
        }
    }

    void deleteLast(){

        if( !isEmpty() ){


            Item * temp = last;
            last = last->prev;
            if ( last ){

                last->next = nullptr;
            }
            delete temp;
            --size;
        }
        else{

            throw "there is no item to delete";
        }
    }

    void putFirst( T const & data ){

        if( !isEmpty() ){

            Item * second = first;
            first = new Item( data, nullptr, second );
            second->prev = first;
            ++size;
		}
        else{

            initialiseContainer( data );
		}
	}

    void putLast( T const & data ){

        if( !isEmpty() ){

            Item * temp = last;
            last = new Item( data, temp, nullptr );
            temp->next = last;
            ++size;

		}
        else{

            initialiseContainer( data );
		}
	}



    void skipIterator(){

        iterator = first;
	}

    bool isNextExist() const {

        if( iterator ){

            return iterator->next != nullptr;
		}
		return false;
	}

    void next(){

        if( iterator ){

            iterator = iterator->next;
		}
        else{

            throw "iterator error";
		}
	}



    Container() : first(nullptr), last (nullptr), iterator(nullptr), size(0)  {}

    Container( T const & data ){
        initialiseContainer( data );
	}

    void clean(){

        if( ! isEmpty() ){

            Item * next = first->next;
            Item * temp = first;

            while( next ){

                delete temp;
                temp = next;
				next = next->next;
			}

            size = 0;
            iterator = nullptr;
            last = nullptr;
            first = nullptr;

            delete temp;
		}
	}


    ~Container(){

        clean();
	}

    struct Item{

    public:

        Item( T const & data1, Item *prev1, Item * next1 ): data(data1), next(next1), prev(prev1){

        }

        T data;
        Item * prev;
        Item * next;

	};


    Item * last;

    Item * first;

private:


    void initialiseContainer( T const & data ){

        size = 1;
        first = new Item( data, nullptr, nullptr );
        last = first;
	}

    Item * iterator;

    int size;
};
