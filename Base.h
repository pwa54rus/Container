class Printable{

public:

    virtual std::string print() const = 0;
};


class Named : public Printable{

protected:

    std::string name;

public:

    Named( std::string const & name1 ) : name(name1) {}


    virtual ~Named(){

    }

    virtual std::string print() const {
        return name;
	}
};
