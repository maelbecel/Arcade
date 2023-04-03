import os
from notion_client import Client
from notion_client.errors import *

def update_database(actor, sha, status):
    # Initialize a new Notion client
    notion = Client(auth=os.environ["NOTION_TOKEN"])

    # Get the database
    database_id = os.environ["DATABASE_ID"]
    database = notion.databases.retrieve(database_id)

    # Create a new entry in the database
    new_page = {
        "Name": {"title": [{"text": {"content": actor}}]},
        "Commit": {"rich_text": [{"text": {"content": sha}}]},
        "Status": {"rich_text": [{"text": {"content": status}}]}
    }

    try:
        database.pages.create(properties=new_page)
        print("Successfully updated Notion database!")
    except (NotionClientError, APIResponseError) as e:
        print(f"Error updating Notion database: {e}")

if __name__ == "__main__":
    import sys
    update_database(sys.argv[1], sys.argv[2], sys.argv[3])