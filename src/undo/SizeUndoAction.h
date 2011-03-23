/*
 * Xournal++
 *
 * Undo action resize
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */
// TODO: AA: type check

#ifndef __SIZEUNDOACTION_H__
#define __SIZEUNDOACTION_H__

#include "UndoAction.h"

class XojPage;
class Layer;
class Redrawable;
class Stroke;

class SizeUndoAction: public UndoAction {
public:
	SizeUndoAction(XojPage * page, Layer * layer, Redrawable * view);
	~SizeUndoAction();

	virtual bool undo(Control * control);
	virtual bool redo(Control * control);
	virtual String getText();

	void addStroke(Stroke * s, double originalWidth, double newWidt, double * originalPressure, double * newPressure,
			int pressureCount);

public:
	static double * getPressure(Stroke * s);

private:
	GList * data;

	Layer * layer;
	Redrawable * view;
};

#endif /* __SIZEUNDOACTION_H__ */