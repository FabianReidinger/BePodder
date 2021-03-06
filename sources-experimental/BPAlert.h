/*******************************************************************************
/
/	File:			Alert.h
/
/	Description:	BPAlert displays a modal alert window.
/
/	Copyright 1993-98, Be Incorporated, All Rights Reserved
/
*******************************************************************************/
 
#ifndef	_ALERT_H
#define	_ALERT_H

#include <BeBuild.h>
#include <Window.h>

class BBitmap;
class BButton;
class BInvoker;
class BTextView;

enum button_spacing {
	B_EVEN_SPACING = 0,
	B_OFFSET_SPACING
};

/*----------------------------------------------------------------*/
/*----- BPAlert class ---------------------------------------------*/

class BPAlert : public BWindow
{
public:

					BPAlert(	const char *title,
							const char *text,
							const char *button1,
							const char *button2 = NULL,
							const char *button3 = NULL,
							button_width width = B_WIDTH_AS_USUAL,
							BBitmap* icon = NULL);
					BPAlert(	const char *title,
							const char *text,
							const char *button1,
							const char *button2,
							const char *button3,
							button_width width,
							button_spacing spacing,
							BBitmap* type = NULL);
virtual				~BPAlert();
	
/* Archiving */
					BPAlert(BMessage *data);
static	BArchivable	*Instantiate(BMessage *data);
virtual	status_t	Archive(BMessage *data, bool deep = true) const;
	
/* BPAlert guts */
		void		SetShortcut(int32 button_index, char key);
		char		Shortcut(int32 button_index) const;

		int32		Go();
		status_t	Go(BInvoker *invoker);

virtual	void		MessageReceived(BMessage *an_event);
virtual	void		FrameResized(float new_width, float new_height);
		BButton		*ButtonAt(int32 index) const;
		BTextView	*TextView() const;

virtual BHandler	*ResolveSpecifier(BMessage *msg,
									int32 index,
									BMessage *specifier,
									int32 form,
									const char *property);
virtual	status_t	GetSupportedSuites(BMessage *data);

virtual void		DispatchMessage(BMessage *msg, BHandler *handler);
virtual	void		Quit();
virtual	bool		QuitRequested();

static	BPoint		AlertPosition(float width, float height);

/*----- Private or reserved -----------------------------------------*/
virtual status_t	Perform(perform_code d, void *arg);

private:
friend class _BPAlertFilter_;

virtual	void		_ReservedAlert1();
virtual	void		_ReservedAlert2();
virtual	void		_ReservedAlert3();

		void		InitObject(const char *text,
							const char *button1,
							const char *button2 = NULL,
							const char *button3 = NULL,
							button_width width = B_WIDTH_AS_USUAL,
							button_spacing spacing = B_EVEN_SPACING,
							BBitmap* icon = NULL);
		BBitmap		*InitIcon();

		sem_id			fAlertSem;
		int32			fAlertVal;
		BButton			*fButtons[3];
		BTextView		*fTextView;
		char			fKeys[3];
		BBitmap*		fIcon;
		button_width	fButtonWidth;
		BInvoker		*fInvoker;
		uint32			_reserved[4];
};

/*-------------------------------------------------------------*/
/*-------------------------------------------------------------*/

// functions to display HTML alerts with Opera

status_t TellTellBrowser(BMessage*m);
status_t TellTellBrowser(BMessage*m,BMessage*r);

#endif /* _ALERT_H */
