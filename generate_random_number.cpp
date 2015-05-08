random_device seed;
mt19337 numberGenerator(seed());
uniform_int_distribution<int> six(1,6);
cout << six(numberGenerator) << endl
