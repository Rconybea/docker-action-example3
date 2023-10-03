Problems checking out source code from within container:
1. container doesn't have permission to invoke the usual github actions/checkout@v3
   Proposed workaround is to have container run with same UID as github runner;
   I haven't tried to pursue that.
2. should be able to share resources between jobs/steps using volumes and/or artifacts
   This seems pretty fussy just to check out some code.
3. Instead added git to docker container,  then run checkout directly.
   Complications:
   - need to introduce a personal access token.  don't want to use `GIT_TOKEN`,
     since that only works for attached repo;  we know we want to pull from multiple repos
     (e.g. see workflow for `github.com:rconybea/reflect`).
     See `GIT_ACCESS_TOKEN` in `.github/workflows/main.yml`
   - git running inside container gives confusing error when it attempts checkout:
     ```
     fatal: unable to access 'https://github.com/rconybea/docker-action-example3.git/': OpenSSL/3.0.8: error:16000069:STORE routines::unregistered scheme
     ```
     This error is misleading - actual problem is that for some reason container doesn't recognize github.com's certificate.
     Wishfully added `nixpkgs.cacert`, to no visible effect.
     Successfully suppressed error by prefixing git commands with `GIT_SSL_NO_VERIFY=true`
   
   
