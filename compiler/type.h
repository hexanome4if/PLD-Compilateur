#include <string>
using namespace std;

typedef enum {
				int64,
				int32,
				ifChar
} TypeName;

class Type {
const string letter[2] = { "q","l" };
int name;
string getLetter() {
				return letter[name];
}

};
