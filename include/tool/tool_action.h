/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013 CERN
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef __TOOL_ACTION_H
#define __TOOL_ACTION_H

#include <string>
#include <wx/wx.h>

#include <tool/tool_base.h>
#include <tool/action_manager.h>

// TOOL_ACTION - represents a single action. For instance:
// - changing layer to top by pressing PgUp
// - running the DRC from the menu
// and so on, and so forth....
class TOOL_ACTION
{
public:
    TOOL_ACTION( const std::string& aName, TOOL_ActionScope aScope = AS_CONTEXT, int aDefaultHotKey = 0,
                 const wxString& aMenuItem = wxT( "" ), const wxString& aMenuDesc = wxT( "" ) ) :
            m_name( aName ), m_scope( aScope ), m_defaultHotKey( aDefaultHotKey ),
                m_currentHotKey( aDefaultHotKey ), m_menuItem( aMenuItem ),
                m_menuDescription( aMenuDesc ), m_id( -1 ), m_actionMgr( NULL )
    {
    }

    ~TOOL_ACTION()
    {
        if( m_actionMgr )
            m_actionMgr->UnregisterAction( this );
    }

    bool operator==( const TOOL_ACTION& aRhs ) const
    {
        return m_id == aRhs.m_id;
    }

    bool operator!=( const TOOL_ACTION& aRhs ) const
    {
        return m_id != aRhs.m_id;
    }

    /**
     * Function GetName()
     * Returns name of the action. It is the same one that is contained in TOOL_EVENT that is
     * sent by activating the TOOL_ACTION.
     *
     * @return Name of the action.
     */
    const std::string& GetName() const
    {
        return m_name;
    }

    /**
     * Function GetId()
     * Returns the unique id of the TOOL_ACTION object. It is valid only after registering the
     * TOOL_ACTION by ACTION_MANAGER.
     *
     * @return The unique identification number. If the number is negative, then it is not valid.
     */
    int GetId() const
    {
        return m_id;
    }

    /**
     * Function ChangeHotKey()
     * Assigns a new hot key.
     *
     * @param aNewHotKey is the new hot key.
     */
    void ChangeHotKey( int aNewHotKey )
    {
        wxASSERT_MSG( false, wxT( "It is not fully implemented yet") );
        // I mean it has to be changed in the ACTION_MANAGER, or change the implementation
        m_currentHotKey = aNewHotKey;
    }

    /**
     * Function RestoreHotKey()
     * Changes the assigned hot key to the default one.
     */
    void RestoreHotKey()
    {
        wxASSERT_MSG( false, wxT( "It is not fully implemented yet") );
        // I mean it has to be changed in the ACTION_MANAGER, or change the implementation
        m_currentHotKey = m_defaultHotKey;
    }

    /**
     * Function HasHotKey()
     * Checks if the action has a hot key assigned.
     *
     * @return True if there is a hot key assigned, false otherwise.
     *
     */
    bool HasHotKey() const
    {
        return m_currentHotKey > 0;
    }

    /**
     * Function GetEvent()
     * Returns the event associated with the action (ie. the event that will be sent after
     * activating the action).
     *
     * @return The event associated with the action.
     */
    TOOL_EVENT GetEvent() const
    {
        return TOOL_EVENT( TC_Command, TA_Action, m_name, m_scope );
    }

private:
    friend class ACTION_MANAGER;

    /// Assigns an unique identifier. It is given by an instance of ACTION_MANAGER.
    void setId( int aId )
    {
        m_id = aId;
    }

    /// Assigns ACTION_MANAGER object that handles the TOOL_ACTION.
    void setActionMgr( ACTION_MANAGER* aManager )
    {
        m_actionMgr = aManager;
    }

    /// Name of the action (convention is: app.[tool.]action.name)
    std::string m_name;

    /// Scope of the action (ie. the event that is issued after activation).
    TOOL_ActionScope m_scope;

    /// Default hot key that activates the action.
    const int m_defaultHotKey;

    /// Custom assigned hot key that activates the action.
    int m_currentHotKey;

    /// Menu entry text
    wxString m_menuItem;

    /// Pop-up help
    wxString m_menuDescription;

    // Icon for menu entry
    //KiBitmap m_bitmap;

    /// Unique ID for fast matching. Assigned by ACTION_MANAGER.
    int m_id;

    /// Action manager that handles this TOOL_ACTION.
    ACTION_MANAGER* m_actionMgr;

    /// Origin of the action
//    const TOOL_BASE* m_origin;

    /// Originating UI object
//    wxWindow* m_uiOrigin;
};
#endif