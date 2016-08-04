package fmpp;

/*
 * Copyright (c) 2003, D�niel D�k�ny
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * - Neither the name "FMPP" nor the names of the project contributors may
 *   be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import java.io.File;

import fmpp.util.ExceptionCC;

/**
 * Error while performing the processing session. 
 */
public class ProcessingException extends ExceptionCC {
    private final File sourceFile;
    private final File sourceRoot;

    /**
     * @param sourceFile can be <code>null</code>.
     */
    public ProcessingException(Engine e, File sourceFile, Throwable cause) {
        super(cause);
        this.sourceRoot = e.getSourceRoot();
        if (sourceRoot != null) {
            this.sourceFile = sourceFile;
        } else {
            this.sourceFile = null;
        }
    }

    /**
     * Returns the source file the faliure relates to.
     * This is an absolute file (not relative).
     * It's <code>null</code> if no such information is available.
     */
    public File getSourceFile() {
        return sourceFile;
    }
    
    /**
     * Returns the "sourceRoot" used during the processing session that failed.
     * It's maybe <code>null</code>, but only if {@link #getSourceFile()}
     * returns <code>null</code> too. 
     */
    public File getSourceRoot() {
        return sourceRoot; 
    }
    
    /**
     * Returns always the same text: "FMPP processing session failed."
     */
    public String getMessage() {
        return "FMPP processing session failed.";
    }
}