import { Alert, Button } from "@mui/material";
import { FormattedMessage } from "react-intl";
import React from "react";

function PageNotFound() {
  return (
    <div>
      <Alert severity="error">
        <FormattedMessage
          id="Whoops! This page was not found"
          defaultMessage="Whoops! This page was not found"
        />
      </Alert>
      <div className="mt-16">
        <Button color="warning" variant="contained" className="" href="/#/">
          <FormattedMessage id="Go back" defaultMessage="Go back" />
        </Button>
      </div>
    </div>
  );
}

export default PageNotFound;
