#ifndef TESTANT_CLASS_HH
#define TESTANT_CLASS_HH

class Testant_Person
{
public:
  int name() {return 0;}

  int birthdate() const {return 0;}

  int age = 11;

  const int birthplace = 12;
};

int country = 13;

const int planet = 3;

int getPlanet() {return planet;}

#endif // #ifndef
