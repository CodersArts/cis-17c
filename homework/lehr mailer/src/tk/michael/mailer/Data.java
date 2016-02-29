package tk.michael.mailer;

import com.michael.api.security.AES;

import javax.swing.*;
import java.io.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;

/**
 * Created by michael on 2/17/2016.
 */
public class Data implements Serializable {
	private String user;
	private String password;
	private String first;
	private String last;
	private Sections sections;

	public Data( String user, String password, String first, String last, Sections sections ) {
		AES.setSalt( "616db35f4359d31c" ); //a53544aa5f8a6ce6614c7783
		try {
			this.user = AES.encrypt( user );
			this.password = AES.encrypt( password );
		} catch ( Exception e ) {
			e.printStackTrace();
			JOptionPane.showMessageDialog( null, "Error saving.", "Error", JOptionPane.ERROR_MESSAGE );
		}
		this.first = first;
		this.last = last;
		this.sections = sections;
	}

	public Data( String user, String password, String first, String last, String sections ) {
		this( user, password, first, last, Sections.parse( sections ) );
	}

	public Data() {
		this.user = "";
		this.password = "";
		this.first = "";
		this.last = "";
		this.sections = new Sections();
	}

	public void seralize(){
		seralize( new File( Utils.getAppDir( "Lehr-Mailer" ), "Data.dat" ) );
	}

	public void seralize( File saveLoaction ) {
		try {
			File outFile = saveLoaction;
			File testFile = outFile;
			if ( !testFile.exists() ) {
				testFile.getParentFile().mkdir();
				testFile.createNewFile();
			}
			FileOutputStream file = new FileOutputStream( outFile );
			ObjectOutputStream out = new ObjectOutputStream( file );
			out.writeObject( this );
			out.close();
			file.close();
		} catch ( IOException e ) {
			e.printStackTrace();
		}
	}

	public static Data load(){
		return load( new File( Utils.getAppDir( "Lehr-Mailer" ), "Data.dat" ) );
	}

	public static Data load( File location ){
		try {
			File outFile = location;
			FileInputStream file = new FileInputStream( outFile );
			ObjectInputStream in = new ObjectInputStream( file );
			Data data = (Data) in.readObject();
			in.close();
			file.close();
			return data;
		} catch ( IOException ignore ){}
		catch(  ClassNotFoundException e ){
			e.printStackTrace();
		}
		return null;
	}

	public String getUser() {
		AES.setSalt( "616db35f4359d31c" );
		try {
			if ( user.isEmpty() ) {
				return "";
			}
			return AES.decrypt( user );
		} catch ( Exception e ) {
			e.printStackTrace();
			return "";
		}
	}

	public void setUser( String user ) {
		this.user = user;
	}

	public String getPassword() {
		AES.setSalt( "616db35f4359d31c" );
		try {
			if ( password.isEmpty() ) {
				return "";
			}
			return AES.decrypt( password );
		} catch ( Exception e ) {
			e.printStackTrace();
			return "";
		}
	}

	public void setPassword( String password ) {
		this.password = password;
	}

	public String getFirst() {
		return first;
	}

	public void setFirst( String first ) {
		this.first = first;
	}

	public String getLast() {
		return last;
	}

	public void setLast( String last ) {
		this.last = last;
	}

	public Sections getSections() {
		return sections;
	}

	public void setSections( Sections sections ) {
		this.sections = sections;
	}

	public String getSubject( String currentSection ){
		SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy");
		Calendar cal = Calendar.getInstance();
		return String.format( "%s, %s - Attendance %s - %s", getLast(), getFirst(), dateFormat.format( cal.getTime() ), currentSection );
	}

	public String getSubject(){
		return getSubject( sections.at( 0 ) );
	}
}