public class MainJNI2 {

	public static void main(String[] args) 
	{
		JNITest test = new JNITest();
		System.out.println("Created test using !");
		char test2[] = "bonjour".toCharArray();
		T_TEST_1 t1 = new T_TEST_1();
		test.Create_T1(t1);
		test.Print_T1_SIMPLE(t1);
		test.Test1(t1);
		test.Print_T1(t1);
	}

}
