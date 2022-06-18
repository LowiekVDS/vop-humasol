import { useEffect } from "react";
import { FormattedMessage } from "react-intl";
import ApiService from "../service/ApiService";
import Button from "../components/Button";
export default function Reset() {
  useEffect(() => {
    ApiService.fetch("/reset", "GET");
  }, []);

  return (
    <>
      <h1 className="text-4xl font-bold">
        <FormattedMessage id={"Reset!"} defaultMessage={"Reset"} />
      </h1>
      <p>
        <FormattedMessage
          id={"Wait until the reset is done!"}
          defaultMessage={"Wait until the reset is done!"}
        />
      </p>
      <Button className="mt-6" onClick={() => (window.location.href = "/")}>
        <FormattedMessage defaultMessage={"go back"} id={"go back"} />
      </Button>
    </>
  );
}
