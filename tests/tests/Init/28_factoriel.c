int factoriel(int n) {
				int res = 1;
				if(n) {
								res = n * factoriel(n-1);
				}
				return res;
}

int main() {
				return factoriel(5);
}
