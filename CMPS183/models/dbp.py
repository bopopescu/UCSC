import datetime

db.define_table('post',
                Field('user_email', default=auth.user.email if auth.user_id else None),
                Field('post_content', 'text', label=T('')),
                Field('created_on', 'datetime', default=datetime.datetime.utcnow()),
                Field('updated_on', 'datetime', update=datetime.datetime.utcnow()),
                )

db.post.user_email.readable = db.post.user_email.writable = False
db.post.post_content.requires = IS_NOT_EMPTY()
db.post.created_on.readable = db.post.created_on.writable = False
db.post.updated_on.readable = db.post.updated_on.writable = False

db.define_table('prof',
                Field('user_email', default=auth.user.email if auth.user_id else None),
                Field('img'),
                Field('hometown', 'text'),
                Field('birthday', 'text'),
                Field('birthyear', 'integer'),
                )

db.prof.user_email.readable = db.prof.user_email.writable = False
db.prof.birthday.requires = IS_NOT_EMPTY()
db.prof.birthyear.requires = IS_NOT_EMPTY()