# -*- coding: utf-8 -*-
# this file is released under public domain and you can use without limitations

# -------------------------------------------------------------------------
# This is a sample controller
# - index is the default action of any application
# - user is required for authentication and authorization
# - download is for downloading files uploaded in the db (does streaming)
# -------------------------------------------------------------------------

def get_user_name_from_email(email):
    """Returns a string corresponding to the user first and last names,
    given the user email."""
    u = db(db.auth_user.email == email).select().first()
    if u is None:
        return 'None'
    else:
        return ' '.join([u.first_name, u.last_name])

def index():
    """
    example action using the internationalization operator T and flash
    rendered by views/default/index.html or views/generic.html

    if you need a simple wiki simply replace the two lines below with:
    return auth.wiki()
    """
    response.flash = T("Hello World")
    return dict(message=T('Welcome to web2py!'))


def user():
    """
    exposes:
    http://..../[app]/default/user/login
    http://..../[app]/default/user/logout
    http://..../[app]/default/user/register
    http://..../[app]/default/user/profile
    http://..../[app]/default/user/retrieve_password
    http://..../[app]/default/user/change_password
    http://..../[app]/default/user/bulk_register
    use @auth.requires_login()
        @auth.requires_membership('group name')
        @auth.requires_permission('read','table name',record_id)
    to decorate functions that need access control
    also notice there is http://..../[app]/appadmin/manage/auth to allow administrator to manage users
    """
    return dict(form=auth())

def main():
    return dict()

def aboutus():
    return dict()

def slco():
    return dict()

def login():
    return dict()

def profile():
    return dict()

def socialconnect():
    if request.args(0) is None:
        form_type = 'create'
        form = SQLFORM(db.post, deletable=True)
    else:
        q = ((db.post.user_email == auth.user.email) &
             (db.post.id == request.args(0)))
        po = db(q).select().first()
        if po is None:
            session.flash = T('Not Authorized')
            redirect(URL('default', 'socialconnect'))

        po.last_opened = datetime.datetime.utcnow()
        po.update_record()
        is_edit = (request.vars.edit == 'true')
        form_type = 'edit' if is_edit else 'view'
        form = SQLFORM(db.post, record=po, deletable=is_edit, readonly=not is_edit, showid=False, formstyle="bootstrap")
    button_list = []
    if form_type == 'edit':
        button_list.append(A('Cancel', _class='w3-btn btn-warning',
                             _href=URL('default', 'edit', args=[po.id])))
    elif form_type == 'create':
        button_list.append(A('Cancel', _class='w3-btn w3-theme-d2',
                             _href=URL('default', 'socialconnect')))
    elif form_type == 'view':
        button_list.append(A('Edit', _class='w3-btn btn-warning',
                             _href=URL('default', 'edit', args=[po.id], vars=dict(edit='true'))))

    if form.process().accepted:
        if form_type == 'create':
            session.flash = T('Post added.')
        elif form_type == 'edit' and form.deleted is False:
            session.flash = T('Post edited.')
        else:
            session.flash = T('Post deleted.')
        redirect(URL('default', 'socialconnect'))
    elif form.errors:
        session.flash = T('Please enter correct values.')
    posts = db(db.post).select(orderby=~db.post.created_on)
    return dict(posts=posts, form=form, g_f_m = get_user_name_from_email, users=db(db.auth_user.id).count())

def edit():
    if request.args(0) is None:
        form_type = 'create'
        form = SQLFORM(db.post, deletable=True)
    else:
        q = ((db.post.user_email == auth.user.email) &
             (db.post.id == request.args(0)))
        po = db(q).select().first()
        if po is None:
            session.flash = T('Not Authorized')
            redirect(URL('default', 'socialconnect'))

        po.last_opened = datetime.datetime.utcnow()
        po.update_record()
        is_edit = (request.vars.edit == 'true')
        form_type = 'edit' if is_edit else 'view'
        form = SQLFORM(db.post, record=po, deletable=is_edit, readonly=not is_edit, showid=False, delete_label='Delete', formstyle="bootstrap")
    button_list = []
    if form_type == 'edit':
        button_list.append(A('Cancel', _class='w3-btn w3-theme-d2',
                             _href=URL('default', 'edit', args=[po.id])))
    elif form_type == 'create':
        button_list.append(A('Cancel', _class='w3-btn w3-theme-d2',
                             _href=URL('default', 'socialconnect')))
    elif form_type == 'view':
        button_list.append(A('Edit', _class='w3-btn w3-theme-d2',
                             _href=URL('default', 'edit', args=[po.id], vars=dict(edit='true'))))
        button_list.append(A('Cancel', _class='w3-btn w3-theme-d1',
                             _href=URL('default', 'socialconnect')))

    if form.process().accepted:
        if form_type == 'create':
            session.flash = T('Post added.')
        elif form_type == 'edit' and form.deleted is False:
            session.flash = T('Post edited.')
        else:
            session.flash = T('Post deleted.')
        redirect(URL('default', 'socialconnect'))
    elif form.errors:
        session.flash = T('Please enter correct values.')
    posts = db(db.post).select(orderby=~db.post.created_on)
    return dict(posts=posts, form=form, button_list=button_list, g_f_m = get_user_name_from_email,
                users=db(db.auth_user.id).count())

def search():
    return dict()

def messenger():
    return dict()

@cache.action()
def download():
    """
    allows downloading of uploaded files
    http://..../[app]/default/download/[filename]
    """
    return response.download(request, db)


def call():
    """
    exposes services. for example:
    http://..../[app]/default/call/jsonrpc
    decorate with @services.jsonrpc the functions to expose
    supports xml, json, xmlrpc, jsonrpc, amfrpc, rss, csv
    """
    return service()


