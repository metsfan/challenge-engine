void printVec3(vec3 &in vec)
{
	print(vec.x + "," + vec.y + "," + vec[2]);
}

void printVec4(vec4 &in vec)
{
	print(vec.x + "," + vec.y + "," + vec[2] + "," + vec.w);
}

void printMat4(mat4 &in mat)
{
	for (int i = 0; i < 4; i++) {
		printVec4(mat[i]);
	}
}

void main(vec2 &in position)
{
	print("Position: " + position.x + "," + position.y);

	vec2 anotherVec;
	anotherVec.x = 3;
	anotherVec.y = 7;

	//vec2 copy = anotherVec;
	//anotherVec += 7.0;
	vec3 test0(7.0f, 3.0f, 6.0f);
	//test0 += 3;

	vec3 test1;
	test1.x = 2;
	test1.y = 6;
	test1.z = 2;

	vec3 test3 = test0 + 5;
	vec3 test4 = test0 + test1;

	//vec3 test2 = test0 * test0;
	vec3 test2 = max(test0, test1);
	vec3 test5 = test2;

	float test6 = dot(test0, test1);

	printVec3(test2); 
	printVec3(test3);
	printVec3(test4);
	printVec3(test5);

	print("" + test6);
}