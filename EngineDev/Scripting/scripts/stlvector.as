void printVec(vector_int &in vec)
{
	print("--start--");

	for (int i = 0; i < vec.size(); i++) {
		print(vec[i] + "");
	}

	print("--end--");
}

void main(vector_int &in vec)
{
	vec.push_back(2);
	vec.push_back(27);

	printVec(vec);

	vec.erase(3); 
	vec.erase(0);

	printVec(vec);

}