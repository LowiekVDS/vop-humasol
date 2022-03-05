import { Button } from "@mui/material";
import { FormattedMessage } from "react-intl";

function PageNotFound() {
  return (
    <div>
      <FormattedMessage defaultMessage={"Whoops! This page was not found"} />
      <Button href="/#/">
        <FormattedMessage defaultMessage={"Go back"} />
      </Button>
    </div>
  );
}

export default PageNotFound;
