void main(vec2 &in position)
{
	print("Position: " + position.x + "," + position.y);

	vec2 anotherVec;
	anotherVec.x = 3;
	anotherVec.y = 7;

	//vec2 copy = anotherVec;
	//anotherVec += 7.0;
	vec3 test0(7.0f, 3.0f, 6.0f);

	vec3 test1;
	test1.x = 2;
	test1.y = 6;
	test1.z = 2;

	//vec3 test2 = test0 * test0;
	vec3 test2 = max(test0, test1);

	float dotProd = dot(test0, test1);

	print("Result: " + test2.x + "," + test2.y + "," + test2.z);
	//print("Result: " + dotProd);
}