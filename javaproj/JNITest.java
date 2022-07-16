
import java.io.File;
import java.lang.reflect.Field ;

public final class JNITest
{
	static {

		try
        {
			System.loadLibrary("result");
			System.out.println ( "Native code loading...") ;
        }
        catch ( UnsatisfiedLinkError e )
        {
            System.err.println ( "Native code library failed to load.\n" + e ) ;
            System.exit ( 1 ) ; 
        }
	}
	
	/**
	 * Pointer to the c++ object
	 */
	private long nativeObjectPointer;
	
	/**
	 * Constructor
	 * @return
	 */
	private native long nativeNew();
	
	public JNITest()
	{
		nativeObjectPointer = nativeNew();
	}

	public native void Set_Test2(int test2[][]);

	public native int Set_Dir(char str[]);

	public native void Create_T1(T_TEST_1 t1);

	public native void Create_T2(T_TEST_2 t2);

	public native void Test3(T_TEST_1 t1,T_TEST_2 t2);

	public native void Test1(T_TEST_1 t1);

	public native void Test2(T_TEST_2 t2);

	public native void Print_T1(T_TEST_1 t1);

	public native void Print_T2(T_TEST_2 t2);

    private T_TEST_1 t1 = new T_TEST_1();
    
    private T_TEST_2 t2 = new T_TEST_2();
}
