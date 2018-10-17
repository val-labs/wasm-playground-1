all:
%:;for f in lesson* ; do make -C $$f $@; done
