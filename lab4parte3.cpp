int main(){
	int n;
	cin >> n;

	Audifono **arr = new Audifono*[n];
	for(int i = 0; i<n; i++){
		arr[i] = new Audifono("Rojo")
	}

	for(int i = 0; i<n; i++){
		delete arr[i];
	}
	delete[] arr;
}