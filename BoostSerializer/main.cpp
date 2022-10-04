#include "boost/archive/xml_oarchive.hpp"
#include <QCoreApplication>
#include <iostream>
#include <fstream>

#define boolean_t unsigned char
#define STATIC  //Generally used for .cpp files to more readable code exercise. This is just a show case for usage. No advantage for compile or runtime build. Only for convention.
#define PUBLIC
#define PRIVATE

struct representive_struct{

    representive_struct():itest{0},dtest{0},stest{0},uctest{0}{
    }
    int itest;
    double dtest;
    short stest;
    boolean_t uctest;
    double arr[8];

    friend class boost::serialization::access;

    template <class Archive>
    PUBLIC void serialize(Archive & ar, const unsigned int version)
    {

        ar & BOOST_SERIALIZATION_NVP(itest);
        ar & BOOST_SERIALIZATION_NVP(dtest);
        ar & BOOST_SERIALIZATION_NVP(stest);
        ar & BOOST_SERIALIZATION_NVP(uctest);
        ar & BOOST_SERIALIZATION_NVP(arr);


    }
};

class representive_class
{
public:
    explicit representive_class();

    void addVecItem(std::string item){
        vtest.push_back(item);
    }

    std::vector<std::string> getVecItem(){
        if(vtest.empty()){
            qWarning()<<"Vector Item Is Empty!";

        }
        return vtest;
    }
private:
    representive_struct data;

    int i_data;
    int p_data;

    representive_class& operator=(representive_class* other)
    {
        this->data=other->data;
        this->i_data=other->i_data;
        this->p_data=other->p_data;
        return *this;
    };

    std::vector<std::string> vtest;
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //operator overload example
        representive_struct test;
        test=data;

        ar & boost::serialization::make_nvp("test",test);
        ar & BOOST_SERIALIZATION_NVP(vtest);
    }

};



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    representive_class position;

    position.addVecItem("Test1");
    position.addVecItem("Test2");

    {
        std::ofstream ofs("C:/Projects/Boost-Serialization-Example/BoostSerializer/output.xml");
        boost::archive::xml_oarchive oa(ofs);

        oa << BOOST_SERIALIZATION_NVP(position);
    }

    return a.exec();
}
