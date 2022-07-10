
import java.io.File;
import java.lang.reflect.Field ;

public final class JNICAsyncSocket 
{
	static {

		try
        {
			System.loadLibrary("casyncsocket_jni");
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
	
	public JNICAsyncSocket()
	{
		nativeObjectPointer = nativeNew();
	}
	
	public native int getSocket();
	
	
	
}
