package tk.michael.mailer;

import com.michael.api.IO.IO;
import com.michael.api.swing.ModalDialog;
import com.michael.api.swing.RegexTextField;
import net.miginfocom.swing.MigLayout;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * Created by michael on 2/24/2016.
 */
public class SectionDialog extends ModalDialog implements ActionListener {
	private RegexTextField section;
	private JList<String> list;
	private DefaultListModel<String> listModel;
	private boolean isDone = false;
	private Sections data = null;

	public SectionDialog( Window parent, Sections data ) {
		super( parent, "Add Sections Numbers", true );
		this.data = data;
		init();
		centerOnParent( dialog, true );
	}

	@Override
	protected void init() {
		JPanel panel = new JPanel( new MigLayout(  ) );

		section = new RegexTextField( true );
		listModel = new DefaultListModel();
		if ( data != null ) {
			for ( int i = 0; i < data.size(); i++ ) {
				listModel.addElement( data.at( i ) );
			}
		}
//		listModel.addElement( "test" );
		list = new JList<>( listModel );


		panel.add( new JLabel( "Add Sections" ), "split 3" );
		panel.add( section, "w 200px"  );
		JButton add = new JButton( "Add" );
		add.setActionCommand( "add" );
		add.addActionListener( this );
		panel.add( add, "wrap" );

		panel.add( new JLabel( "Sections" ), "wrap" );
		panel.add( new JScrollPane( list ), "w 100%, wrap" );

		JButton remove = new JButton( "Remove" );
		remove.setActionCommand( "remove" );
		remove.addActionListener( this );
		panel.add( remove, "align center, wrap" );

		panel.add( new JSeparator(  ), "w 100%, wrap" );
		JButton btn = new JButton( "Done" );
		btn.setActionCommand( "done" );
		btn.addActionListener( this );
		panel.add( btn, "align right, split 2" );

		btn = new JButton( "Cancel" );
		btn.setActionCommand( "cancel" );
		btn.addActionListener( this );
		panel.add( btn, "wrap" );

		dialog.setDefaultCloseOperation( JDialog.DISPOSE_ON_CLOSE );
		dialog.setContentPane( panel );
		dialog.setLocationRelativeTo( parent );
		dialog.pack();
	}

	public void centerOnParent(final Window child, final boolean absolute) {
		child.pack();
		boolean useChildsOwner = child.getOwner() != null ? ((child.getOwner() instanceof JFrame) || (child.getOwner() instanceof JDialog)) : false;
		final Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		final Dimension parentSize = useChildsOwner ? child.getOwner().getSize() : screenSize ;
		final Point parentLocationOnScreen = useChildsOwner ? child.getOwner().getLocationOnScreen() : new Point(0,0) ;
		final Dimension childSize = child.getSize();
		childSize.width = Math.min(childSize.width, screenSize.width);
		childSize.height = Math.min(childSize.height, screenSize.height);
		child.setSize(childSize);
		int x;
		int y;
		if ((child.getOwner() != null) && child.getOwner().isShowing()) {
			x = (parentSize.width - childSize.width) / 2;
			y = (parentSize.height - childSize.height) / 2;
			x += parentLocationOnScreen.x;
			y += parentLocationOnScreen.y;
		} else {
			x = (screenSize.width - childSize.width) / 2;
			y = (screenSize.height - childSize.height) / 2;
		}
		if (!absolute) {
			x /= 2;
			y /= 2;
		}
		child.setLocation(x, y);
	}

	@Override
	public void actionPerformed( ActionEvent e ) {
		String action = e.getActionCommand();

		if ( action.equals( "add" ) ) {
			if ( section.matches() ) {
				listModel.addElement( section.getText().trim() );
			} else{

			}
		}

		if ( action.equals( "remove" ) ) {
			listModel.remove( list.getSelectedIndex() );
		}

		if ( action.equals( "cancel" ) ) {
			dialog.dispose();
		}

		if ( action.equals( "done" ) ) {
			String[] sections = new String[listModel.getSize()];
			for( int i = 0; i < listModel.getSize(); i++ ){
				if ( !listModel.get( i ).trim().isEmpty() ) {
					sections[i] = listModel.get( i ).trim();
				}
			}
			data = new Sections( sections );
			isDone = true;
			dialog.dispose();
		}
	}

	public Sections displayReturnData(){
		display();
		if ( isDone ) {
			return data;
		} else {
			return null;
		}
	}
}
