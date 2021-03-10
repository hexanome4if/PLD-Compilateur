class Type {

    typedef enum {
        int64,
        int32
    } TypeName;

    
    const string letter[] = { "q","l" };
    int name;
    string getLetter() {return letter[name];}

};