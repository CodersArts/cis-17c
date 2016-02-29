package tk.michael.mailer;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Vector;

/**
 * Created by michael on 2/24/2016.
 */
public class Sections implements Serializable{
	private Vector<String> sections = new Vector<>();

	public Sections( String[] sections ) {
		this.sections.addAll( Arrays.asList( sections ) );
	}

	public Sections( String section ) {
		this.sections.add( section );
	}

	public Sections() {
		this.sections = null;
	}

	public String toString(){
		if ( sections == null ) { return "";}
		if ( sections.size() > 0) {
			StringBuilder sb = new StringBuilder();

			for( int i = 0; i < sections.size(); i++ ){
				sb.append( sections.get( i ) ).append( "," );
			}

			sb.deleteCharAt( sb.length() - 1 );

			return sb.toString();
		} else {
			return "";
		}
	}

	public int size(){
		if ( sections == null ) {
			return 0;
		}
		return sections.size();
	}

	public String at( int i ){
		return sections.get( i );
	}

	public static Sections parse( String input ){
		if ( input.isEmpty() ) {
			return null;
		}
		String[] temp = input.split( "," );
		for( int i = 0; i < temp.length; i++ ){
			temp[i] = temp[i].trim();
		}
		return new Sections( temp );
	}
}
