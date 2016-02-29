package tk.michael.mailer;

import java.io.File;
import tk.michael.mailer.EnumOs;
/**
 * Created by michael on 2/17/2016.
 */
public class Utils {
	private static final int BASE = 36;
	public static final int[] osint = new int[EnumOs.values().length];
	public static final File BYPASS_FILE = new File( "./bypass.dat" );

	static {
		try {
			Utils.osint[EnumOs.LINUX.ordinal()] = 1;
		}
		catch (NoSuchFieldError var0) {
			// empty catch block
		}
		try {
			Utils.osint[EnumOs.SOLARIS.ordinal()] = 2;
		}
		catch (NoSuchFieldError var0_1) {
			// empty catch block
		}
		try {
			Utils.osint[EnumOs.WINDOWS.ordinal()] = 3;
		}
		catch (NoSuchFieldError var0_2) {
			// empty catch block
		}
		try {
			Utils.osint[EnumOs.MACOS.ordinal()] = 4;
		}
		catch (NoSuchFieldError var0_3) {
			// empty catch block
		}
	}

	public static File getAppDir(String nm) {
		File f;
		String var1 = System.getProperty("user.home", ".");
		switch (Utils.getOs()) {
			case LINUX:
			case SOLARIS: {
				f = new File(var1, String.valueOf('.') + nm + '/');
				break;
			}
			case WINDOWS: {
				String var3 = System.getenv("APPDATA");
				if (var3 != null) {
					f = new File(var3, "." + nm + '/');
					break;
				}
				f = new File(var3, String.valueOf('.') + nm + '/');
				break;
			}
			case MACOS: {
				f = new File(var1, "Library/Application Support/" + nm);
				break;
			}
			default: {
				f = new File(var1, String.valueOf(nm) + '/');
			}
		}
		if (!f.exists() && !f.mkdirs()) {
			throw new RuntimeException("The working directory could not be created " + f);
		}
		return f;
	}

	public static EnumOs getOs() {
		String os = System.getProperty("os.name").toLowerCase();
		if ( os.contains( "win" ) ) {
			return EnumOs.WINDOWS;
		}
		else if( os.contains( "mac" ) ){
			return EnumOs.MACOS;
		}
		else if ( os.contains( "solaris" ) || os.contains( "sunos" ) ) {
			return EnumOs.SOLARIS;
		}
		else if ( os.contains( "linux" ) || os.contains( "unix" )) {
			return EnumOs.LINUX;
		}
		return EnumOs.UNKNOWN;
	}

	public static boolean bypassExists(){
		File bypassFile = BYPASS_FILE;
		return bypassFile.exists();
	}
}
