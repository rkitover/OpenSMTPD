include	$(top_srcdir)/mk/pathnames

pkglibexec_PROGRAMS =	mail.mboxfile

mail_mboxfile_SOURCES = $(smtpd_srcdir)/mail.mboxfile.c
mail_mboxfile_SOURCES+= $(smtpd_srcdir)/log.c

AM_CPPFLAGS=		-I$(top_srcdir)/smtpd			\
			-I$(top_srcdir)/openbsd-compat
if !SUPPORT_ERR_H
AM_CPPFLAGS += -I$(top_srcdir)/openbsd-compat/err_h
endif

LIBCOMPAT =		$(top_builddir)/openbsd-compat/libopenbsd-compat.a

LDADD = 		$(LIBCOMPAT)




uninstall-hook:
	rmdir	$(DESTDIR)$(pkglibexecdir) 2> /dev/null || /bin/true
