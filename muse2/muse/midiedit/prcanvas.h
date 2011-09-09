//=========================================================
//  MusE
//  Linux Music Editor
//    $Id: prcanvas.h,v 1.5.2.6 2009/11/16 11:29:33 lunar_shuttle Exp $
//  (C) Copyright 1999 Werner Schweer (ws@seh.de)
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; version 2 of
//  the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//
//=========================================================

#ifndef __PRCANVAS_H__
#define __PRCANVAS_H__

#include "ecanvas.h"
#include "pianoroll.h"
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QTimer>

#include "steprec.h"

#define KH        13

//---------------------------------------------------------
//   NEvent
//    ''visual'' Note Event
//---------------------------------------------------------

class NEvent : public MusEWidget::CItem {
   public:
      NEvent(Event& e, Part* p, int y);
      };

class ScrollScale;
class PianoRoll;
class QRect;

//---------------------------------------------------------
//   PianoCanvas
//---------------------------------------------------------

class PianoCanvas : public EventCanvas {
      Q_OBJECT
    
      int colorMode;
      int playedPitch;
      
      bool noteHeldDown[128];
      
      StepRec* steprec;

      
      virtual void viewMouseDoubleClickEvent(QMouseEvent*);
      virtual void drawItem(QPainter&, const MusEWidget::CItem*, const QRect&);
      void drawTopItem(QPainter &p, const QRect &rect);
      virtual void drawMoving(QPainter&, const MusEWidget::CItem*, const QRect&);
      virtual Undo moveCanvasItems(MusEWidget::CItemList&, int, int, DragType);
      virtual UndoOp moveItem(MusEWidget::CItem*, const QPoint&, DragType);
      virtual MusEWidget::CItem* newItem(const QPoint&, int);
      virtual void resizeItem(MusEWidget::CItem*, bool noSnap, bool);
      virtual void newItem(MusEWidget::CItem*, bool noSnap);
      virtual bool deleteItem(MusEWidget::CItem*);
      virtual void startDrag(MusEWidget::CItem* item, bool copymode);
      virtual void dragEnterEvent(QDragEnterEvent* event);
      virtual void dragMoveEvent(QDragMoveEvent*);
      virtual void dragLeaveEvent(QDragLeaveEvent*);
      virtual void addItem(Part*, Event&);

      int y2pitch(int) const;
      int pitch2y(int) const;
      virtual void drawCanvas(QPainter&, const QRect&);
      virtual void itemPressed(const MusEWidget::CItem*);
      virtual void itemReleased(const MusEWidget::CItem*, const QPoint&);
      virtual void itemMoved(const MusEWidget::CItem*, const QPoint&);
      virtual void curPartChanged();
      virtual void resizeEvent(QResizeEvent*);

   private slots:
      void midiNote(int pitch, int velo);

   signals:
      void quantChanged(int);
      void rasterChanged(int);
      void newWidth(int);

   public slots:
      void pianoCmd(int);
      void pianoPressed(int pitch, int velocity, bool shift);
      void pianoReleased(int pitch, bool);

   public:
      enum {
         CMD_CUT, CMD_COPY, CMD_PASTE, CMD_DEL,
         CMD_QUANTIZE,
         CMD_SELECT_ALL, CMD_SELECT_NONE, CMD_SELECT_INVERT,
         CMD_SELECT_ILOOP, CMD_SELECT_OLOOP, CMD_SELECT_PREV_PART, CMD_SELECT_NEXT_PART, 
         CMD_MODIFY_GATE_TIME, CMD_MODIFY_VELOCITY, CMD_CRESCENDO,
         CMD_TRANSPOSE, CMD_THIN_OUT, CMD_ERASE_EVENT,
         CMD_NOTE_SHIFT, CMD_MOVE_CLOCK, CMD_COPY_MEASURE,
         CMD_ERASE_MEASURE, CMD_DELETE_MEASURE, CMD_CREATE_MEASURE,
         CMD_FIXED_LEN, CMD_DELETE_OVERLAPS, CMD_LEGATO
         };

      PianoCanvas(MidiEditor*, QWidget*, int, int);
      void cmd(int cmd);
      void setColorMode(int mode) {
            colorMode = mode;
            redraw();
            }
      virtual void modifySelected(MusEWidget::NoteInfo::ValType type, int delta);
      };
#endif

