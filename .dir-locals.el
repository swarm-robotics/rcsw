;;; .dir-locals.el --

;;; Commentary:

;;; Code:
((c-mode .
  ((eval  . (progn
                  (require 'rtags-init)
                  (require 'irony-mode-init)
                  (let ((cc-search-dirs (list (concat (projectile-project-root) "include/rcsw/*")
                                              (concat (projectile-project-root) "src/*/src/*")
                                              (concat (projectile-project-root) "include"))
                                        ))
                    (setq cc-search-directories cc-search-dirs))

                  (let ((includes-list (list
                                        (substitute-in-file-name "$rcsw/include")
                                        (substitute-in-file-name "$rcsw/ext")
                                        (concat (projectile-project-root) "include")
                                        )))
                    (setq flycheck-clang-include-path includes-list)
                    (setq flycheck-gcc-include-path includes-list)
                    (setq compile-command (concat "make -C" (concat (projectile-project-root) "build")))
                    (add-hook 'c-mode-hook 'google-style-hook)
                    (setq flycheck-clang-args '("-std=gnu99"))
                    (setq flycheck-gcc-args '("-std=gnu99"))
                  )
              )
         ))
  ))

;;; end of .dir-locals.el
