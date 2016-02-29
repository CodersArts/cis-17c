package tk.michael.mailer;

import com.michael.api.swing.ModalDialog;
import com.michael.api.swing.RegexTextField;
import net.miginfocom.swing.MigLayout;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by michael on 2/17/2016.
 */
public class OptionsDialog extends ModalDialog implements ActionListener {
	private HashMap<String, RegexTextField> fields = new HashMap<>();
	private JPasswordField password;
	private Data data;
	private boolean save;
	private boolean isDone = false;

	public OptionsDialog( Frame parent ) {
		this( parent, true );
	}

	//only makes the bypass
	public OptionsDialog( Frame parent, boolean save ) {
		super( parent, "Email Options", true );
		this.save = save;
		data = Data.load();
		if ( data == null ) {
			data = new Data();
		}
		init();
		centerOnParent( dialog, true );
	}

	@Override
	protected void init() {
		JPanel panel = new JPanel( new MigLayout() );

		fields.put( "user", new RegexTextField( data.getUser(), true ) );
		password = new JPasswordField();
		password.setText( data.getPassword() );
		fields.put( "first", new RegexTextField( data.getFirst(), true ) );
		fields.put( "last", new RegexTextField( data.getLast(), true ) );
		fields.put( "section", new RegexTextField( data.getSections().toString(), true ) );
		if ( data.getSections().size() > 1 ) {
			fields.get( "section" ).setEnabled( false );
		}

		JPanel pane = new JPanel( new MigLayout() );
		pane.add( new JLabel( "Email:" ), "wrap" );
		pane.add( fields.get( "user" ), "w 200px, wrap" );
		panel.add( pane, "split 2, pad 0 0 0 0 " );

		pane = new JPanel( new MigLayout() );
		pane.add( new JLabel( "Password:" ), "wrap" );
		pane.add( password, "w 200px, wrap" );
		panel.add( pane, "wrap, pad 0 0 0 0" );

		pane = new JPanel( new MigLayout() );
		pane.add( new JLabel( "First Name" ), "wrap" );
		pane.add( fields.get( "first" ), "w 200px, wrap" );
		panel.add( pane, "split 2, pad 0 0 0 0" );

		pane = new JPanel( new MigLayout() );
		pane.add( new JLabel( "Last Name" ), "wrap" );
		pane.add( fields.get( "last" ), "w 200px, wrap" );
		panel.add( pane, "wrap, pad 0 0 0 0" );

		pane = new JPanel( new MigLayout() );
		pane.add( new JLabel( "Section Number" ), "wrap" );
		pane.add( fields.get( "section" ), "w 200px" );
		JButton moreSections = new JButton( "Add more" );
		moreSections.setActionCommand( "moreSections" );
		moreSections.addActionListener( this );
		pane.add( moreSections );
		panel.add( pane, "pad 0 0 0 0, wrap" );

		panel.add( new JSeparator(), "w 100%, wrap" );
		JButton btn = new JButton( "Cancel" );
		btn.setActionCommand( "cancel" );
		btn.addActionListener( this );
		panel.add( btn, "split 2, align center" );

		btn = new JButton( "Ok" );
		btn.setActionCommand( "ok" );
		btn.addActionListener( this );
		panel.add( btn );

//		JCheckBox checkBox = new JCheckBox( "Remember Me" );
//		checkBox.setSelected(  );

		dialog.setDefaultCloseOperation( JDialog.DISPOSE_ON_CLOSE );
		dialog.setContentPane( panel );
		dialog.setLocationRelativeTo( parent );
		dialog.pack();
	}

	public void centerOnParent( final Window child, final boolean absolute ) {
		child.pack();
		boolean useChildsOwner = child.getOwner() != null ? ( ( child.getOwner() instanceof JFrame ) || ( child.getOwner() instanceof JDialog ) ) : false;
		final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		final Dimension parentSize = useChildsOwner ? child.getOwner().getSize() : screenSize;
		final Point parentLocationOnScreen = useChildsOwner ? child.getOwner().getLocationOnScreen() : new Point( 0, 0 );
		final Dimension childSize = child.getSize();
		childSize.width = Math.min( childSize.width, screenSize.width );
		childSize.height = Math.min( childSize.height, screenSize.height );
		child.setSize( childSize );
		int x;
		int y;
		if ( ( child.getOwner() != null ) && child.getOwner().isShowing() ) {
			x = ( parentSize.width - childSize.width ) / 2;
			y = ( parentSize.height - childSize.height ) / 2;
			x += parentLocationOnScreen.x;
			y += parentLocationOnScreen.y;
		} else {
			x = ( screenSize.width - childSize.width ) / 2;
			y = ( screenSize.height - childSize.height ) / 2;
		}
		if ( !absolute ) {
			x /= 2;
			y /= 2;
		}
		child.setLocation( x, y );
	}

	@Override
	public void actionPerformed( ActionEvent e ) {
		String action = e.getActionCommand();

		if ( action.equals( "cancel" ) ) {
			dialog.dispose();
		}

		if ( action.equals( "moreSections" ) ) {
			SectionDialog sc = new SectionDialog( dialog, Sections.parse( fields.get( "section" ).getText() ) );
			Sections sections = sc.displayReturnData();
			if ( sections != null ) {
				if ( sections.size() > 1 ) {
					fields.get( "section" ).setEnabled( false );
				} else{
					fields.get( "section" ).setEnabled( true );
				}
				fields.get( "section" ).setText( sections.toString() );
			}
		}

		if ( action.equals( "ok" ) ) {
			String pass = new String( password.getPassword() );
			boolean passed = true;
			String error = "<html><p>Fix the following errors</p><ul>";
			for ( Map.Entry<String, RegexTextField> entry : fields.entrySet() ) {
				String key = entry.getKey();
				RegexTextField value = entry.getValue();
				if ( key.equals( "section" ) ) {
					continue;
				}
				if ( !value.matches() ) {
					passed = false;
					error += "<li>Fill in the " + key + " field</li>";
				}
			}

			if ( pass.length() <= 0 ) {
				error += "<li>Fill in the password field</li>";
				passed = false;
			}
			error += "</ul></html>";
			if ( passed ) {
				error = null;
				data = new Data(
						fields.get( "user" ).getText(),
						pass,
						fields.get( "first" ).getText(),
						fields.get( "last" ).getText(),
						fields.get( "section" ).getText()
				);
				if ( save ) {
					data.seralize();
				} else {
					data.seralize( Utils.BYPASS_FILE );
					JOptionPane.showMessageDialog( dialog, "Created \"bypass.dat\" in working directory" );
				}
				isDone = true;
				dialog.dispose();
			} else {
				JOptionPane.showMessageDialog( dialog, error );
			}

		}
	}

	public Data displayReturnData() {
		display();
		if ( isDone ) {
			return data;
		} else {
			return null;
		}
	}
}
