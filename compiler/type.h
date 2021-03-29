typedef enum {
				int64,
				int32
} TypeName;

class Type {
				const string letter[2] = { "q","l" };
				int name;
				string getLetter() {
								return letter[name];
				}

};
