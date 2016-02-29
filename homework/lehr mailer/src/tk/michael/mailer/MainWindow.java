package tk.michael.mailer;

import com.michael.api.email.Emailer;
import com.michael.api.swing.BasicFrameObject;
import com.michael.api.swing.MenuHelper;
import com.michael.api.swing.RegexTextField;
import com.michael.api.swing.SwingHelper;
import net.miginfocom.swing.MigLayout;

import javax.mail.MessagingException;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by michael on 2/17/2016.
 */
public class MainWindow extends BasicFrameObject implements ActionListener{
	private HashMap< String, RegexTextField > fields = new HashMap<>(  );
	private ArrayList<String> sections = new ArrayList<>(  );
	DefaultComboBoxModel comboBoxModel;
	private JComboBox<String> sectionCombo;
	private JRadioButton[] radioButtons = new JRadioButton[]{ new JRadioButton( "BCC" ), new JRadioButton( "CC" ) };
	private Data data;
	private static final String version = "0.1a";
	private static String[] arguments;
	private JLabel attachmentLabel;
	private String attachmentFile = null;

	public static void main( String[] args ){
		try {
			SwingHelper.setLookAndFeel( "Nimbus" );
		} catch ( Exception ignore ) {}
		MainWindow window = new MainWindow( args );
		window.display();
//		SectionDialog sd = new SectionDialog( window.frame );
//		sd.display();
	}

	public static boolean hasArg( String test ) {
		if ( Arrays.asList( arguments ).indexOf( test ) > -1 ) {
			return true;
		}
		return false;
	}

	public MainWindow( String[] args ) {
		super( "Lehr Mailer" );
		arguments = args;
		init();
	}

	@Override
	protected void init() {
		comboBoxModel = new DefaultComboBoxModel();
		sectionCombo = new JComboBox<>( comboBoxModel );
		// load the data from file
		//check if there is a bypass
		if( Utils.bypassExists() ){
			data = Data.load( Utils.BYPASS_FILE );
			fields.put( "from", new RegexTextField( data.getUser(), true ) );
			for( int i = 0; i < data.getSections().size(); i++ ){
				comboBoxModel.addElement( data.getSections().at( i ) );
			}
			fields.put( "subject", new RegexTextField( data.getSubject( data.getSections().at( 0 )), true ) );
		} else {
			data = Data.load();
			if( data != null ){
				fields.put( "from", new RegexTextField( data.getUser(), true ) );
				for( int i = 0; i < data.getSections().size(); i++ ){
					comboBoxModel.addElement( data.getSections().at( i ) );
				}
				fields.put( "subject", new RegexTextField( data.getSubject(), true ) );
			}
		}
		// gui loading
		initMenu();
		JPanel panel = new JPanel( new MigLayout(  ) );

		fields.put( "to", new RegexTextField( "mark.lehr@rcc.edu", true ) );
		fields.put( "word", new RegexTextField( true ) );
		if( data == null ){
			fields.put( "from", new RegexTextField( true ) );
			fields.put( "subject", new RegexTextField( true ) );
		}

		JPanel pane = new JPanel( new MigLayout(  ) );
		pane.add( new JLabel( "To:" ) , "wrap");
		pane.add( fields.get( "to" ), "w 200px, wrap" );
		panel.add( pane, "split 2, pad 0 0 0 0 " );

		pane = new JPanel( new MigLayout(  ) );
		pane.add( new JLabel( "From:" ) , "wrap");
		pane.add( fields.get( "from" ), "w 200px, wrap" );
		panel.add( pane, "wrap, pad 0 0 0 0" );

		pane = new JPanel( new MigLayout(  ) );
		pane.add( new JLabel( "Word of the Day:" ) , "wrap");
		pane.add( fields.get( "word" ), "w 200px, wrap" );
		panel.add( pane, "split 2, pad 0 0 0 0" );

		pane = new JPanel( new MigLayout(  ) );
		pane.add( new JLabel( "Subject" ) , "wrap");
		pane.add( fields.get( "subject" ), "w 200px, wrap" );
		panel.add( pane, "wrap, pad 0 0 0 0" );

		//section buttons if needed
		pane = new JPanel( new MigLayout( "align right" ) );
		pane.add( new JLabel( "Select Section Number" ), "split 2" );
		pane.add( sectionCombo, "w 200px" );
		panel.add( pane, "wrap, align right" );
		sectionCombo.addActionListener( this );

		//bcc/cc buttons
		ButtonGroup btnGroup = new ButtonGroup();
		btnGroup.add( radioButtons[0] );
		btnGroup.add( radioButtons[1] );

		pane = new JPanel( new MigLayout(  ) );
		pane.add( radioButtons[0], "split 2, align left" );
		pane.add( radioButtons[1] );
		radioButtons[0].setSelected( true );
		panel.add( pane, "split 2, width max(100, 50%)" );

		pane = new JPanel( new MigLayout( "align right" ) );
		attachmentLabel = new JLabel( "Attachments" );
		pane.add( attachmentLabel, "split 2" );
		JButton attachments = new JButton( "Browse" );
		attachments.setActionCommand( "attach" );
		attachments.addActionListener( this );
		pane.add( attachments, "align right" );
		panel.add( pane, "wrap, width max(100, 50%)" );

		panel.add( new JSeparator(  ), "w 100%, wrap" );
		JButton btn = new JButton( "Options" );
		btn.setActionCommand( "options" );
		btn.addActionListener( this );
		panel.add( btn, "split 2, align center" );

		btn = new JButton( "Send" );
		btn.setActionCommand( "send" );
		btn.addActionListener( this );
		panel.add( btn );

		frame.add( panel );
		frame.pack();
		frame.setDefaultCloseOperation( WindowConstants.EXIT_ON_CLOSE );
		frame.setLocationRelativeTo( null );
	}

	@Override
	protected void initMenu() {
		JMenuBar menuBar = new JMenuBar();
		JMenu advancedMenu = new JMenu( "Advanced" );
		MenuHelper.createMenuItem( advancedMenu, MenuHelper.PLAIN, "Make Bypass", "mkBypass", 0, this );
		MenuHelper.createMenuItem( advancedMenu, MenuHelper.CHECK, "Use Bypass", "useBypass", 0, this ).setSelected( true );

		menuBar.add( advancedMenu );
		frame.setJMenuBar( menuBar );
	}

	@Override
	public void actionPerformed( ActionEvent e ) {
		String action = e.getActionCommand();

		if ( action.equals( "options" ) ) {
			OptionsDialog od = new OptionsDialog( frame );
			data = od.displayReturnData();
			if ( data != null ) {
				fields.get( "from" ).setText( data.getUser() );
				fields.get( "subject" ).setText( data.getSubject() );
				comboBoxModel.removeAllElements();
				for( int i = 0; i < data.getSections().size(); i++ ){
					comboBoxModel.addElement( data.getSections().at( i ) );
				}
			}
		}

		if ( action.equals( "attach" ) ) {
			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setCurrentDirectory( new File( "." ) );
			int returnValue = fileChooser.showOpenDialog( frame );
			attachmentFile = null;
			if ( returnValue == JFileChooser.APPROVE_OPTION ) {
				File selectedFile = fileChooser.getSelectedFile();
				attachmentLabel.setText( ".../" + selectedFile.getName() );
				attachmentFile = selectedFile.toString();
			} else if( returnValue == JFileChooser.CANCEL_OPTION ){
				attachmentFile = null;
				attachmentLabel.setText( "Attachments" );
			}
		}

		if ( action.equals( "mkBypass" ) ) {
			OptionsDialog od = new OptionsDialog( frame, false );
			od.display();
		}

		if ( action.equals( "useBypass" ) ) {
			Object src = e.getSource();
			if( ( (JMenuItem)src ).isSelected() ){
				if( Utils.bypassExists() ){
					data = Data.load( Utils.BYPASS_FILE );
					fields.get( "from").setText( data.getUser() );
					fields.get( "subject" ).setText( data.getSubject() );
				}
			} else{
				data = Data.load();
				if( data != null ){
					fields.get( "from").setText( data.getUser() );
					fields.get( "subject" ).setText( data.getSubject() );
				}
			}
		}

		if ( e.getSource().equals( sectionCombo ) ) {
			fields.get( "subject" ).setText( data.getSubject( (String)comboBoxModel.getElementAt( sectionCombo.getSelectedIndex() ) ) );

		}

		if ( action.equals( "send" ) ) {
			boolean passed = true;
			String error = "<html><p>Fix the following errors</p><ul>";
			for ( Map.Entry<String, RegexTextField> entry : fields.entrySet() ) {
				String key = entry.getKey();
				RegexTextField value = entry.getValue();
				if ( !value.matches() ) {
					passed = false;
					error += "<li>Fill in the " + key + " field</li>";
				}
			}
			error += "</ul></html>";
			if ( passed ) {
				error = null;
				try {
					if ( radioButtons[0].isSelected() ) { // if bcc is selected
						Emailer.sendGmail( data.getUser(), data.getPassword(), fields.get( "to" ).getText(), "", data.getUser(), fields.get( "subject" ).getText(), fields.get( "word" ).getText() );
//						Emailer.sendGmail( data.getUser(), data.getPassword(), "rishermichael@gmail.com", "", data.getUser(), fields.get( "subject" ).getText(), fields.get( "word" ).getText(), attachmentFile );
						JOptionPane.showMessageDialog(null, "Message Sent!");
					} else {
						Emailer.sendGmail( data.getUser(), data.getPassword(), fields.get( "to" ).getText(), data.getUser(), "", fields.get( "subject" ).getText(), fields.get( "word" ).getText() );
//						Emailer.sendGmail( data.getUser(), data.getPassword(), "rishermichael@gmail.com", data.getUser(), "", fields.get( "subject" ).getText(), fields.get( "word" ).getText(), attachmentFile );
						JOptionPane.showMessageDialog(null, "Message Sent!");
					}
					//sendGmail( final String gmail, final String pass, String[] to, String[] cc, String[] bcc, String subject, String msg ) throws MessagingException {
				} catch ( MessagingException e1 ) {
					// temporary error catching
					JTextArea textArea = new JTextArea(e1.toString());
					JScrollPane scrollPane = new JScrollPane( textArea );
					textArea.setLineWrap(true);
					textArea.setWrapStyleWord(true);
					scrollPane.setPreferredSize( new Dimension( 500, 250 ) );
					JOptionPane.showMessageDialog( null, scrollPane, "Error", JOptionPane.OK_OPTION );
				}
			} else {
				JOptionPane.showMessageDialog( frame, error );
			}
		}
	}
}
